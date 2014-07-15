/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "game_hack.h"

#include <common/fatal_construction_exception.h>

#include <string>
#include <vector>

#include <common/fatal_error.h>
#include <common/logging.h>

#include <common/resource_exception.h>
#include <common/resource_manager.h>
#include <engine/transform_component.h>

#include <engine/engine.h>
#include <engine/space.h>
#include <engine/logic_component_base.h>
#include <engine/sprite_component.h>
#include <engine/transform_component.h>

#include <graphics/error_checking.h>
#include <graphics/shader_program.h>
#include <graphics/vertex.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>

namespace LE
{

unique_id<logic_component_base> const game_hack_component::type_id;

game_hack_component::game_hack_component(entity & owner) :
  logic_component_base(owner)
{
  LE_FATAL_ERROR_IF(get_owning_entity() == nullptr, "Owner is null!");
  LE_FATAL_ERROR_IF(get_owning_entity()->get_owning_space() == nullptr, "Space is null!");
  space * game_space = get_owning_entity()->get_owning_space();

  {
    auto * new_ent = game_space->create_entity("player");
    new_ent->get_component<transform_component>()->set_pos(0.0f, 100.0f);
    new_ent->get_component<transform_component>()->set_scale(1.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::get_resource_dir() + "textures/player.png");
  }
  {
    auto * new_ent = game_space->create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(-200.0f, -100.0f);
    new_ent->get_component<transform_component>()->set_scale(2.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::get_resource_dir() + "textures/enemy.png");
  }
  {
    auto * new_ent = game_space->create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(200.0f, -100.0f);
    new_ent->get_component<transform_component>()->set_scale(2.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::get_resource_dir() + "textures/enemy.png");
  }
}

void game_hack_component::update(float dt)
{
  LE_FATAL_ERROR_IF(get_owning_entity() == nullptr, "Owner is null!");
  LE_FATAL_ERROR_IF(get_owning_entity()->get_owning_space() == nullptr, "Space is null!");
  space * game_space = get_owning_entity()->get_owning_space();

  p_input(get_owning_entity()->get_owning_space(), dt);
  p_logic(game_space, dt);
  p_physics(game_space, dt);
}

void game_hack_component::p_input(space * game_space, float dt)
{
  float const player_movement_speed = 256.0f;

  // TODO - get_owning_entity vs get_entity?
  auto const* game_engine = get_owning_entity()->get_owning_space()->get_owning_engine();
  auto const& input_sys = game_engine->get_input_system();
  auto * player = game_space->find_entity("player");

  if(input_sys.is_key_pressed(SDLK_o))
  {
    p_ddraw_enabled = !p_ddraw_enabled;
  }

  if(player)
  {
    auto * player_t = player->get_component<transform_component>();

    if(input_sys.is_key_triggered(SDLK_SPACE))
    {
      auto * new_bullet = game_space->create_entity("bullet");
      auto * new_bullet_t = new_bullet->get_component<transform_component>();
      new_bullet_t->set_pos(player_t->get_pos());
      new_bullet_t->set_scale(1.0f);

      new_bullet->create_component<sprite_component>(
      resource_manager::get_resource_dir() + "textures/bullet.png");
    }

    auto const& player_old_pos = player->get_component<transform_component>()->get_pos();
    vec2 player_transl = vec2::zero;
    if(input_sys.is_key_pressed(SDLK_w))
    {
      player_transl[1] = player_movement_speed * dt;
    }
    if(input_sys.is_key_pressed(SDLK_s))
    {
      player_transl[1] = -player_movement_speed * dt;
    }
    if(input_sys.is_key_pressed(SDLK_a))
    {
      player_transl[0] = -player_movement_speed * dt;
    }
    if(input_sys.is_key_pressed(SDLK_d))
    {
      player_transl[0] = player_movement_speed * dt;
    }
    player_t->translate(player_transl);

    if(player_transl != vec2::zero)
    {
      if(p_ddraw_enabled)
      {
        game_space->m_world_ddraw.lines.add_arrow(
          player_old_pos, player_transl / dt, vec4mk(1.0f, 0.0f, 0.0f, 1.0f));

        game_space->m_world_ddraw.points.add_point(
          player_old_pos, vec4mk(0.0f, 0.0f, 1.0f, 1.0f));
      }
    }
  }
}

void game_hack_component::p_logic(space * game_space, float dt)
{
  float const bullet_movement_speed = 512.0f;

  float const enemy_seek_radius = 256.0f;
  float const enemy_movement_speed = 64.0f;

  auto * player = game_space->find_entity("player");
  if(player)
  {
    auto * player_t = player->get_component<transform_component>();

    for(auto entity_it = game_space->entity_begin();
        entity_it != game_space->entity_end();
        ++entity_it)
    {
      // Enemy seeking
      auto & curr_entity = (*entity_it).second;
      if(curr_entity->get_name() == "enemy")
      {
        auto * enemy_t = curr_entity->get_component<transform_component>();

        if(p_ddraw_enabled)
        {
          game_space->m_world_ddraw.lines.add_circle(
            enemy_t->get_pos(), enemy_seek_radius, vec4mk(1.0f, .0f, 1.0f, 1.0f));
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
              enemy_t->get_pos(), dir_to_player, enemy_seek_radius, vec4mk(1.0f, 0.0f, 1.0f, 1.0f));
          }
        }
      }
      // Bullet logic
      else if(curr_entity->get_name() == "bullet")
      {
        // TODO velocity
        curr_entity->get_component<transform_component>()->translate(0.0f, -bullet_movement_speed * dt);
      }
    }
  }
}

void game_hack_component::p_physics(space * game_space, float dt)
{
  LE_UNUSED_VAR(dt);
  // Quick and dirty hack until actual physics is in place.
  std::vector<entity *> curr_ents;
  curr_ents.reserve(game_space->entity_num());
  for(auto entity_it = game_space->entity_begin();
      entity_it != game_space->entity_end();
      ++entity_it)
  {
    curr_ents.emplace_back((*entity_it).second.get());
  }

  // n^2 collision detection using circles based on pos/scale
  for(auto ent_outer_it = curr_ents.begin(); ent_outer_it != curr_ents.end(); ++ent_outer_it)
  {
    // Don't consider this object or ones before it for testing (they've already been tested).
    for(auto ent_inner_it = curr_ents.begin() + 1; ent_inner_it != curr_ents.end(); ++ent_inner_it)
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

      if(p_ddraw_enabled)
      {
        game_space->m_world_ddraw.lines.add_circle(
          ent_inner_t->get_pos(),
          ent_inner_radius,
          vec4mk(1.0f, 1.0f, 1.0f, 1.0f));
        game_space->m_world_ddraw.lines.add_circle(
          ent_outer_t->get_pos(),
          ent_outer_radius,
          vec4mk(1.0f, 1.0f, 1.0f, 1.0f));
      }

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

} // namespace LE
