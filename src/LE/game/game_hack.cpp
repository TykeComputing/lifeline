/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "game_hack.h"

#include <LE/common/fatal_construction_exception.h>

#include <string>
#include <vector>

#include <LE/common/dt_timer.h>
#include <LE/common/fatal_error.h>
#include <LE/common/logging.h>
#include <LE/common/resource_exception.h>
#include <LE/common/resource_manager.h>
#include <LE/engine/tilemap_component.h>
#include <LE/engine/transform_component.h>
#include <LE/engine/engine.h>
#include <LE/engine/space.h>
#include <LE/engine/logic_component_base.h>
#include <LE/engine/sprite_component.h>
#include <LE/engine/transform_component.h>
#include <LE/engine/TTF_system.h>
#include <LE/graphics/error_checking.h>
#include <LE/graphics/shader_program.h>
#include <LE/graphics/vertex.h>
#include <LE/graphics/vertex_array.h>
#include <LE/graphics/vertex_buffer.h>

namespace LE
{

////////////////////////////////////////////////////////////////////////////////////////////////
class physics_component : public engine_component_base
{
public:
  static unique_id<engine_component_base> const type_id;
};

unique_id<engine_component_base> const physics_component::type_id;

////////////////////////////////////////////////////////////////////////////////////////////////
class AI_seek : public logic_component_base
{
public:
  typedef unique_id<entity> target_id_t;

  AI_seek(float speed, float range, target_id_t const& target_id) :
    AI_seek(speed, range)
  {
    set_target(target_id);
  }

  AI_seek(float speed, float range) :
    p_speed(speed), p_range(range)
  {
  }

  virtual void update(float dt)
  {
    if(p_target_id == target_id_t::null.value())
    {
      return;
    }

    auto * owning_entity = get_owning_entity();
    auto * owning_space = owning_entity->get_owning_space();

    auto * const target_ent = owning_space->find_entity(p_target_id);
    if(target_ent == nullptr)
    {
      p_target_id = target_id_t::null.value();
      return;
    }

    auto * const this_t = owning_entity->get_component<transform_component>();
    auto * const target_t = target_ent->get_component<transform_component>();

    if(owning_space->get_ddraw_enabled())
    {
      owning_space->m_world_ddraw.lines.add_circle(
        this_t->get_pos(), p_range, vec4(1.0f, 0.0f, 1.0f, 1.0f));
    }

    vec2 dir_to_target = target_t->get_pos() - this_t->get_pos();
    float dist_to_target;
    normalize(dir_to_target, dist_to_target);

    // Seek target if either in range or we have an infinite (negative) range
    if( (dist_to_target <= p_range) || (p_range < 0.0f) )
    {
      // TODO - Use phyics
      this_t->translate(dir_to_target * p_speed * dt);

      if(owning_space->get_ddraw_enabled())
      {
        owning_space->m_world_ddraw.lines.add_arrow(
          this_t->get_pos(),
          dir_to_target,
          p_range,
          vec4(1.0f, 0.0f, 1.0f, 1.0f));
      }
    }
  }

  void set_target(target_id_t const& target_id)
  {
    p_target_id = target_id.value();
  }

  void set_speed(float speed)
  {
    p_speed = speed;
  }

  void set_range(float range)
  {
    p_range = range;
  }

  static unique_id<logic_component_base> const type_id;

private:
  float p_speed = 0.0f;
  //! Range at which seeking logic will occur. A negative radius indicates an infinite range.
  float p_range = -1.0f;
  target_id_t::value_type p_target_id = target_id_t::null.value();
};
unique_id<logic_component_base> const AI_seek::type_id;
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
class bullet_movement : public logic_component_base
{
public:
  virtual void update(float dt)
  {
    get_owning_entity()->get_component<transform_component>()->translate(
      0.0f,
      -bullet_movement_speed * dt);
  }

  // TODO - Replace with phyics
  float const bullet_movement_speed = 512.0f;

  static unique_id<logic_component_base> const type_id;
};

unique_id<logic_component_base> const bullet_movement::type_id;
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
class slime_tumor_spread : public logic_component_base
{
public:
  slime_tumor_spread(float spread_time) :
    p_spread_timer(spread_time), p_max_spread_time(spread_time)
  {
  }

  virtual void update(float dt)
  {
    if(p_spread_timer.advance(dt))
    {
      //log_status(log_scope::GAME, "Slime spreading!");
      p_spread_timer.set_target_time((std::rand() / (float)RAND_MAX) * p_max_spread_time);
      p_spread_timer.reset();

      auto * tm = get_owning_entity()->get_component<tilemap_component>();
      LE_FATAL_ERROR_IF(tm == nullptr, "Error");
      tm->set_tile_id(0, 0, 4);

      std::vector<uvec2> existing_slime_pos;
      auto num = tm->count_num_tile_id_instances(4);
      existing_slime_pos.reserve(num);

      uvec2 num_tiles = tm->get_num_tiles();
      for(unsigned y = 0; y < num_tiles.y(); ++y)
      {
        for(unsigned x = 0; x < num_tiles.x(); ++x)
        {
          if(tm->get_tile_id(x, y) == 4)
          {
            existing_slime_pos.emplace_back(x, y);
          }
        }
      }

      auto make_slime_tile = [&tm](
        unsigned x,
        unsigned y)
      {
        auto curr_tile_id = tm->try_get_tile_id(x, y);
        if(curr_tile_id != 4 && tilemap_component::tile_exists(curr_tile_id))
        {
          if(std::rand() % 4)
          {
            tm->set_tile_id(x, y, 4);
          }
        }
      };

      for(uvec2 const& pos : existing_slime_pos)
      {
        make_slime_tile(pos.x() + 1, pos.y());
        make_slime_tile(pos.x() - 1, pos.y());
        make_slime_tile(pos.x(), pos.y() - 1);
        make_slime_tile(pos.x(), pos.y() + 1);
      }
    }
  }

  static unique_id<logic_component_base> const type_id;

private:
  dt_countup p_spread_timer;
  float p_max_spread_time;
};

unique_id<logic_component_base> const slime_tumor_spread::type_id;
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
class enemy_damage : public logic_component_base
{
public:
  static unique_id<logic_component_base> const type_id;
};

unique_id<logic_component_base> const enemy_damage::type_id;
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
class bullet_damage : public logic_component_base
{
public:
  bullet_damage(unique_id<entity> const& shooter_id) :
    p_shooter_id(shooter_id.value())
  {
  }

  unique_id<entity>::value_type get_shooter_id() const { return p_shooter_id; }

  static unique_id<logic_component_base> const type_id;

private:
  unique_id<entity>::value_type const p_shooter_id;
};

unique_id<logic_component_base> const bullet_damage::type_id;
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
class player_controls : public logic_component_base
{
public:
  virtual void update(float dt)
  {
    entity * const player_ent = get_owning_entity();
    if(player_ent == nullptr)
    {
      return;
    }

    space * const owning_space = player_ent->get_owning_space();
    input_system const& input_sys = owning_space->get_owning_engine()->get_input_system();

    auto * const player_t = player_ent->get_component<transform_component>();

    // Shooting
    if(input_sys.is_key_triggered(SDLK_SPACE) || input_sys.is_key_pressed(SDLK_m))
    {
      entity * new_bullet_ent = owning_space->create_entity("bullet");
      auto * new_bullet_t = new_bullet_ent->get_component<transform_component>();
      new_bullet_t->set_pos(player_t->get_pos());
      new_bullet_t->set_scale(1.0f);

      new_bullet_ent->create_component<sprite_component>(
        resource_manager::load<texture2D>("textures/bullet.png"));
      new_bullet_ent->create_component<physics_component>();
      new_bullet_ent->create_component<bullet_movement>();
      new_bullet_ent->create_component<bullet_damage>(player_ent->get_id());
    }

    // Movement
    auto const& player_old_pos = player_ent->get_component<transform_component>()->get_pos();
    vec2 player_transl = vec2::zero;
    if(input_sys.is_key_pressed(SDLK_w))
    {
      player_transl.y() = m_player_movement_speed * dt;
    }
    if(input_sys.is_key_pressed(SDLK_s))
    {
      player_transl.y() = -m_player_movement_speed * dt;
    }
    if(input_sys.is_key_pressed(SDLK_a))
    {
      player_transl.x() = -m_player_movement_speed * dt;
    }
    if(input_sys.is_key_pressed(SDLK_d))
    {
      player_transl.x() = m_player_movement_speed * dt;
    }
    player_t->translate(player_transl);

    if(player_transl != vec2::zero)
    {
      if(owning_space->get_ddraw_enabled())
      {
        owning_space->m_world_ddraw.lines.add_arrow(
          player_old_pos, player_transl / dt, vec4(1.0f, 0.0f, 0.0f, 1.0f));

        owning_space->m_world_ddraw.points.add_point(
          player_old_pos, vec4(0.0f, 0.0f, 1.0f, 1.0f));
      }
    }
  }

  float const m_player_movement_speed = 256.0f;

  static unique_id<logic_component_base> const type_id;
};

unique_id<logic_component_base> const player_controls::type_id;
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

unique_id<logic_component_base> const game_hack::type_id;

void game_hack::initialize()
{
  LE_FATAL_ERROR_IF(get_owning_entity() == nullptr, "Owner is null!");
  LE_FATAL_ERROR_IF(get_owning_entity()->get_owning_space() == nullptr, "Space is null!");
  space * game_space = get_owning_entity()->get_owning_space();

  entity * player = nullptr;
  {
    auto * new_ent = game_space->create_entity("player");
    player = new_ent;
    new_ent->get_component<transform_component>()->set_pos(0.0f, 100.0f);
    new_ent->get_component<transform_component>()->set_scale(1.0f);
    new_ent->create_component<sprite_component>(
      resource_manager::load<texture2D>("textures/player.png"));
    new_ent->create_component<physics_component>();
    new_ent->create_component<player_controls>();
  }
  {
    auto * new_ent = game_space->create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(-200.0f, -100.0f);
    new_ent->get_component<transform_component>()->set_scale(2.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::load<texture2D>("textures/enemy.png"));
    new_ent->create_component<physics_component>();
    new_ent->create_component<AI_seek>(64.0f, 256.0f, player->get_id());
    new_ent->create_component<enemy_damage>();
  }
  {
    auto * new_ent = game_space->create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(200.0f, -100.0f);
    new_ent->get_component<transform_component>()->set_scale(2.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::load<texture2D>("textures/enemy.png"));
    new_ent->create_component<physics_component>();
    new_ent->create_component<AI_seek>(64.0f, 256.0f, player->get_id());
    new_ent->create_component<enemy_damage>();
  }
  {
    auto * new_ent = game_space->create_entity("tilemap");
    vec2 half_rt_size(
      game_space->get_owning_engine()->get_graphics_system().get_render_target_size() / 2);
    new_ent->get_component<transform_component>()->set_pos(-half_rt_size.x(), half_rt_size.y());
    new_ent->get_component<transform_component>()->set_scale(1.0f);

    new_ent->create_component<tilemap_component>(
      resource_manager::full_dir("tilemaps/test.tm"));

    new_ent->create_component<slime_tumor_spread>(1.0f);

    //auto * new_ai_seek = new_ent->create_component<AI_seek>(128.0f, -256.0f, player->get_id());
  }

  auto * pv = p_get_perf_vis_component();
  if(pv)
  {
    p_set_perf_vis_overlapped(pv);

    pv->set_graph_color("update", vec4(0.0f, 0.0f, 1.0f, 1.0f));
    pv->set_graph_color("graphics_system", vec4(1.0f, 0.0f, 0.0f, 1.0f));
    pv->set_graph_color("buffer_swap", vec4(1.0f, 1.0f, 0.0f, 1.0f));
    pv->set_graph_color("total_frame", vec4(0.0f, 1.0f, 0.0f, 1.0f));
  }
}

void game_hack::update(float dt)
{
  LE_FATAL_ERROR_IF(get_owning_entity() == nullptr, "Owner is null!");
  LE_FATAL_ERROR_IF(get_owning_entity()->get_owning_space() == nullptr, "Space is null!");

  p_input();
  p_physics(dt);
}

void game_hack::p_input()
{
  // TODO - get_owning_entity vs get_entity (etc.)?
  auto * const game_space = get_owning_entity()->get_owning_space();
  auto * const game_engine = game_space->get_owning_engine();
  auto const& input_sys = game_engine->get_input_system();

  // Exit
  if(input_sys.is_key_triggered(SDLK_ESCAPE))
  {
    game_engine->set_is_running(false);
  }

  // Reset
  if(input_sys.is_key_triggered(SDLK_RETURN))
  {
    game_space->kill();
    auto * new_game_space = game_engine->create_space("game");
    auto * new_game_hack_ent = new_game_space->create_entity("game_hack");
    new_game_hack_ent->create_component<LE::game_hack>();
  }

  // Toggle debug drawing on/off
  if(input_sys.is_key_triggered(SDLK_o))
  {
    game_space->set_ddraw_enabled(!game_space->get_ddraw_enabled());
  }

  // Toggle perf vis on/off
  if(input_sys.is_key_triggered(SDLK_p))
  {
    auto * perf_vis_space = p_get_perf_vis_space();
    if(perf_vis_space)
    {
      perf_vis_space->set_is_active(!perf_vis_space->get_is_active());
    }
  }

  // Perf vis mode - default fullscreen
  if(input_sys.is_key_pressed(SDLK_LSHIFT))
  {
    if(input_sys.is_key_triggered(SDLK_LEFTBRACKET))
    {
      auto * perf_vis_comp = p_get_perf_vis_component();
      if(perf_vis_comp)
      {
        perf_vis_comp->set_max_time(0.016f);
      }
    }

    // Perf vis mode - default fullscreen
    if(input_sys.is_key_triggered(SDLK_RIGHTBRACKET))
    {
      auto * perf_vis_comp = p_get_perf_vis_component();
      if(perf_vis_comp)
      {
        perf_vis_comp->set_max_time(0.004f);
      }
    }
  }
  else
  {
    if(input_sys.is_key_triggered(SDLK_LEFTBRACKET))
    {
      auto * perf_vis_comp = p_get_perf_vis_component();
      if(perf_vis_comp)
      {
        p_set_perf_vis_overlapped(perf_vis_comp);
      }
    }

    // Perf vis mode - default fullscreen
    if(input_sys.is_key_triggered(SDLK_RIGHTBRACKET))
    {
      auto * perf_vis_comp = p_get_perf_vis_component();
      if(perf_vis_comp)
      {
        p_set_perf_vis_vertical(perf_vis_comp);
      }
    }
  }
}

void game_hack::p_physics(float dt)
{
  LE_UNUSED_VAR(dt);

  auto * game_space = get_owning_entity()->get_owning_space();

  // Quick and dirty hack until actual physics is in place.
  std::vector<entity *> curr_ents;
  curr_ents.reserve(game_space->entity_num());
  for(auto physics_comp_it = game_space->engine_component_begin<physics_component>();
    physics_comp_it != game_space->engine_component_end<physics_component>();
    ++physics_comp_it)
  {
    curr_ents.emplace_back((*physics_comp_it)->get_owning_entity());
  }

  // n^2 collision detection using circles based on pos/scale
  for(auto ent_outer_it = curr_ents.begin(); ent_outer_it != curr_ents.end(); ++ent_outer_it)
  {
    // Don't consider this object or ones before it for testing (they've already been tested).
    for(auto ent_inner_it = ent_outer_it + 1;
        ent_inner_it != curr_ents.end();
        ++ent_inner_it)
    {
      auto ent_outer = (*ent_outer_it);
      auto ent_inner = (*ent_inner_it);

      auto * ent_outer_t = ent_outer->get_component<transform_component>();
      auto * ent_inner_t = ent_inner->get_component<transform_component>();

      auto * ent_outer_sprite = ent_outer->get_component<sprite_component>();
      auto * ent_inner_sprite = ent_inner->get_component<sprite_component>();

      if(!ent_outer_sprite || !ent_inner_sprite)
      {
        continue;
      }

      float const ent_outer_radius =
        ent_outer_t->get_scale_x() * ent_outer_sprite->get_dimensions().x() * 0.5f;

      float const ent_inner_radius =
        ent_inner_t->get_scale_x() * ent_inner_sprite->get_dimensions().x() * 0.5f;

      float const dist_sq =
        length_sq(ent_inner_t->get_pos() - ent_outer_t->get_pos());
      float const r_sum = ent_outer_radius + ent_inner_radius;

      float r_sum_sq = r_sum * r_sum;
      if(dist_sq <= r_sum_sq)
      {
        entity * ents[2] = { ent_outer, ent_inner };

        // No collision messages implemented, the results of a collision are acted upon here for
        //   now
        for(int ent_check_it = 0; ent_check_it < 2; ++ent_check_it)
        {
          // Kill non-enemies that collide with enemies
          if(ents[ent_check_it]->get_component<enemy_damage>())
          {
            // Enemies don't kill other enemies
            if(ents[!ent_check_it]->get_component<enemy_damage>() == false)
            {
              ents[!ent_check_it]->kill();
            }
          }
          // Kill enemies that collide with bullts
          if(ents[ent_check_it]->get_component<bullet_damage>())
          {
            // Don't kill on collision with shooter or other bullets
            if(ents[ent_check_it]->get_component<bullet_damage>()->get_shooter_id() !=
               ents[!ent_check_it]->get_id().value()
            && ents[!ent_check_it]->get_component<bullet_damage>() == nullptr)
            {
              ents[0]->kill();
              ents[1]->kill();
            }
          }
        }
      }
    }
  }
}

space * game_hack::p_get_perf_vis_space()
{
  return get_owning_entity()->get_owning_space()->get_owning_engine()->find_space("perf_vis");
}

perf_vis * game_hack::p_get_perf_vis_component()
{
  auto * perf_vis_space = p_get_perf_vis_space();
  if(perf_vis_space)
  {
    auto * perf_vis_ent = perf_vis_space->find_entity("perf_vis");
    if(perf_vis_ent)
    {
      return perf_vis_ent->get_component<perf_vis>();
    }
  }

  return nullptr;
}

void game_hack::p_set_perf_vis_overlapped(perf_vis * pv) const
{
  pv->set_bottom_left(vec2(-200.f, -100.f));
  pv->set_dimensions(vec2(400.f, 200.f));
  pv->set_offset_percent(vec2::zero);
  pv->set_text_height(16);
  pv->set_graph_name_offset(2);
}

void game_hack::p_set_perf_vis_vertical(perf_vis * pv) const
{
  pv->set_bottom_left(vec2(-64.f, -100.f));
  pv->set_dimensions(vec2(128.f, 32.f));
  pv->set_offset_percent(vec2(0.f, 1.25f));
  pv->set_text_height(12);
  pv->set_graph_name_offset(2);
}

} // namespace LE
