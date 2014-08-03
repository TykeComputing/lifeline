/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "game_hack.h"

#include <LE/common/fatal_construction_exception.h>

#include <string>
#include <vector>

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

/////////////////////
class physics_component : public engine_component_base
{
public:
  static unique_id<engine_component_base> const type_id;
};

unique_id<engine_component_base> const physics_component::type_id;

class AI_seek : public logic_component_base
{
public:
  static unique_id<logic_component_base> const type_id;
};

unique_id<logic_component_base> const AI_seek::type_id;

class bullet : public logic_component_base
{
public:
  static unique_id<logic_component_base> const type_id;
};

unique_id<logic_component_base> const bullet::type_id;
/////////////////////

unique_id<logic_component_base> const game_hack::type_id;

void game_hack::initialize()
{
  LE_FATAL_ERROR_IF(get_owning_entity() == nullptr, "Owner is null!");
  LE_FATAL_ERROR_IF(get_owning_entity()->get_owning_space() == nullptr, "Space is null!");
  space * game_space = get_owning_entity()->get_owning_space();

  {
    auto * new_ent = game_space->create_entity("player");
    new_ent->get_component<transform_component>()->set_pos(0.0f, 100.0f);
    new_ent->get_component<transform_component>()->set_scale(1.0f);
    new_ent->create_component<sprite_component>(
      resource_manager::load<texture2D>("textures/player.png"));
    new_ent->create_component<physics_component>();
  }
  {
    auto * new_ent = game_space->create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(-200.0f, -100.0f);
    new_ent->get_component<transform_component>()->set_scale(2.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::load<texture2D>("textures/enemy.png"));
    new_ent->create_component<physics_component>();
    new_ent->create_component<AI_seek>();
  }
  {
    auto * new_ent = game_space->create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(200.0f, -100.0f);
    new_ent->get_component<transform_component>()->set_scale(2.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::load<texture2D>("textures/enemy.png"));
    new_ent->create_component<physics_component>();
    new_ent->create_component<AI_seek>();
  }
  {
    auto * new_ent = game_space->create_entity("tilemap");
    new_ent->get_component<transform_component>()->set_pos(0.0f, 0.0f);
    new_ent->get_component<transform_component>()->set_scale(1.0f);

    new_ent->create_component<tilemap_component>(
      resource_manager::load<tileset>("tilesets/test/test.tsd"));
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

  p_input(dt);
  p_logic(dt);
  p_physics(dt);
}

void game_hack::p_input(float dt)
{
  float const player_movement_speed = 256.0f;

  // TODO - get_owning_entity vs get_entity (etc.)?
  auto * const game_space = get_owning_entity()->get_owning_space();
  auto * const game_engine = game_space->get_owning_engine();
  auto const& input_sys = game_engine->get_input_system();
  auto * const player = game_space->find_entity("player");

  // Exit
  if(input_sys.is_key_triggered(SDLK_ESCAPE))
  {
    game_engine->set_is_running(false);
  }

  // Reset
  if(input_sys.is_key_triggered(SDLK_RETURN))
  {
    game_space->kill_all();
    auto * new_game_hack_ent = game_space->create_entity("game_hack");
    new_game_hack_ent->create_component<game_hack>();
  }

  // Toggle debug drawing on/off
  if(input_sys.is_key_triggered(SDLK_o))
  {
    p_ddraw_enabled = !p_ddraw_enabled;
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

  // Player controls
  if(player)
  {
    auto * const player_t = player->get_component<transform_component>();

    // Shooting
    if(input_sys.is_key_triggered(SDLK_SPACE) || input_sys.is_key_pressed(SDLK_m))
    {
      auto * new_bullet = game_space->create_entity("bullet");
      auto * new_bullet_t = new_bullet->get_component<transform_component>();
      new_bullet_t->set_pos(player_t->get_pos());
      new_bullet_t->set_scale(1.0f);

      new_bullet->create_component<sprite_component>(
        resource_manager::load<texture2D>("textures/bullet.png"));
      new_bullet->create_component<physics_component>();
      new_bullet->create_component<bullet>();
    }

    // Movement
    auto const& player_old_pos = player->get_component<transform_component>()->get_pos();
    vec2 player_transl = vec2::zero;
    if(input_sys.is_key_pressed(SDLK_w))
    {
      player_transl.y() = player_movement_speed * dt;
    }
    if(input_sys.is_key_pressed(SDLK_s))
    {
      player_transl.y() = -player_movement_speed * dt;
    }
    if(input_sys.is_key_pressed(SDLK_a))
    {
      player_transl.x() = -player_movement_speed * dt;
    }
    if(input_sys.is_key_pressed(SDLK_d))
    {
      player_transl.x() = player_movement_speed * dt;
    }
    player_t->translate(player_transl);

    if(player_transl != vec2::zero)
    {
      if(p_ddraw_enabled)
      {
        game_space->m_world_ddraw.lines.add_arrow(
          player_old_pos, player_transl / dt, vec4(1.0f, 0.0f, 0.0f, 1.0f));

        game_space->m_world_ddraw.points.add_point(
          player_old_pos, vec4(0.0f, 0.0f, 1.0f, 1.0f));
      }
    }
  }
}

// Super hacky/simple game logic
void game_hack::p_logic(float dt)
{
  float const bullet_movement_speed = 512.0f;

  float const enemy_seek_radius = 256.0f;
  float const enemy_movement_speed = 64.0f;

  auto * game_space = get_owning_entity()->get_owning_space();

  auto * const player = game_space->find_entity("player");
  if(player)
  {
    auto * const player_t = player->get_component<transform_component>();

    // Enemy seeking
    for(auto ai_seek_it = game_space->logic_component_begin<AI_seek>();
        ai_seek_it != game_space->logic_component_end<AI_seek>();
        ++ai_seek_it)
    {
      auto * curr_entity = (*ai_seek_it)->get_owning_entity();
      auto * const enemy_t = curr_entity->get_component<transform_component>();

      if(p_ddraw_enabled)
      {
        game_space->m_world_ddraw.lines.add_circle(
          enemy_t->get_pos(), enemy_seek_radius, vec4(1.0f, .0f, 1.0f, 1.0f));
      }

      vec2 dir_to_player =
          player_t->get_pos() - enemy_t->get_pos();
      float dist_to_player;
      normalize(dir_to_player, dist_to_player);

      if(dist_to_player <= enemy_seek_radius)
      {
        enemy_t->translate(dir_to_player * enemy_movement_speed * dt);

        if(p_ddraw_enabled)
        {
          game_space->m_world_ddraw.lines.add_arrow(
            enemy_t->get_pos(),
            dir_to_player,
            enemy_seek_radius,
            vec4(1.0f, 0.0f, 1.0f, 1.0f));
        }
      }
    }

    // Bullet logic
    for(auto bullet_it = game_space->logic_component_begin<bullet>();
        bullet_it != game_space->logic_component_end<bullet>();
        ++bullet_it )
    {
      auto * curr_entity = (*bullet_it)->get_owning_entity();

      curr_entity->get_component<transform_component>()->translate(
        0.0f,
        -bullet_movement_speed * dt);
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
    for(auto ent_inner_it = curr_ents.begin() + 1;
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

        auto ent_involved_in_collision =
          [](std::string const& name,
            entity * (&ents)[2],
            unsigned & index,
            unsigned & other_index)->bool
        {
          if(ents[0]->get_name() == name)
          {
            index = 0;
            other_index = 1;
            return true;
          }
          else if(ents[1]->get_name() == name)
          {
            index = 1;
            other_index = 0;
            return true;
          }

          return false;
        };

        unsigned index;
        unsigned other_index;
        // Hacky collision logic
        if(ent_involved_in_collision("player", ents, index, other_index))
        {
          if(ents[other_index]->get_name() == "enemy")
          {
            ents[index]->kill();
          }
        }
        if(ent_involved_in_collision("enemy", ents, index, other_index))
        {
          if(ents[other_index]->get_name() == "bullet")
          {
            ents[index]->kill();
            ents[other_index]->kill();
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
