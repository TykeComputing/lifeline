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

//////////////////////////////////////////////////////////////////////////
game_hack_scene::game_hack_scene(space * owner) :
  p_owner(owner)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glLineWidth(2.0f);
  glPointSize(5.0f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  p_perf_vis.set_label_color("graphics", vec4(1.0f, 0.0f, 0.0f, 1.0f));
  p_perf_vis.set_label_color("physics", vec4(1.0f, 1.0f, 0.0f, 1.0f));
  p_perf_vis.set_label_color("physics", vec4(0.0f, 0.0f, 1.0f, 1.0f));
  p_perf_vis.set_label_color("update_total", vec4(0.0f, 1.0f, 0.0f, 1.0f));

  {
    auto * new_ent = p_owner->create_entity("player");
    new_ent->get_component<transform_component>()->set_pos(0.0f, 100.0f);
    new_ent->get_component<transform_component>()->set_scale(1.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::get_resource_dir() + "textures/player.png");
  }
  {
    auto * new_ent = p_owner->create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(-200.0f, -100.0f);
    new_ent->get_component<transform_component>()->set_scale(2.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::get_resource_dir() + "textures/enemy.png");
  }
  {
    auto * new_ent = p_owner->create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(200.0f, -100.0f);
    new_ent->get_component<transform_component>()->set_scale(2.0f);

    new_ent->create_component<sprite_component>(
      resource_manager::get_resource_dir() + "textures/enemy.png");
  }
}

game_hack_scene::~game_hack_scene()
{
}

// returns false if a quit message has been received
bool game_hack_scene::input(space & game_space, float dt)
{
  float const player_movement_speed = 256.0f;

  auto * player = game_space.find_entity("player");

  SDL_Event curr_event;
  while(SDL_PollEvent(&curr_event))
  {
    switch(curr_event.type)
    {

    //////////////////////////////////////////////////////////////////////////
    // Hacky handling of triggered/release key states
    case SDL_KEYDOWN:
    {
      if(curr_event.key.repeat == false)
      {
        switch(curr_event.key.keysym.sym)
        {

        case SDLK_SPACE:
        {
          if(player)
          {
            auto * player_t = player->get_component<transform_component>();

            auto * new_bullet = game_space.create_entity("bullet");
            auto * new_bullet_t = new_bullet->get_component<transform_component>();
            new_bullet_t->set_pos(player_t->get_pos());
            new_bullet_t->set_scale(1.0f);

            new_bullet->create_component<sprite_component>(
              resource_manager::get_resource_dir() + "textures/bullet.png");
          }
        }
        break;

        // Shader reloading
        case SDLK_RETURN:
        {

        }
        break;

        // Shader reloading
        case SDLK_o:
        {
          p_ddraw_enabled = !p_ddraw_enabled;
        }
        break;

        case SDLK_ESCAPE:
        {
          return false;
        }
        break;

        }
      }
    }
    break;
    //////////////////////////////////////////////////////////////////////////

    case SDL_QUIT:
    {
      return false;
    }
    break;

    }
  }

  // Hacky handling of pressed key states
  // Per SDL2 documentation, (https://wiki.libsdl.org/SDL_GetKeyboardState) pointer returned by
  //   SDL_GetKeyboardState is valid for lifetime of program, thus I only get it once.
  int num_SDL_keys;
  static Uint8 const* const SDL_keys = SDL_GetKeyboardState(&num_SDL_keys);

  if(player)
  {
    auto * player_t = player->get_component<transform_component>();

    // 1 = key pressed, 0 = key not pressed
    auto const& player_old_pos = player->get_component<transform_component>()->get_pos();
    vec2 player_transl = vec2::zero;
    if(SDL_keys[SDL_SCANCODE_W])
    {
      player_transl[1] = player_movement_speed * dt;
    }
    if(SDL_keys[SDL_SCANCODE_S])
    {
      player_transl[1] = -player_movement_speed * dt;
    }
    if(SDL_keys[SDL_SCANCODE_A])
    {
      player_transl[0] = -player_movement_speed * dt;
    }
    if(SDL_keys[SDL_SCANCODE_D])
    {
      player_transl[0] = player_movement_speed * dt;
    }
    player_t->translate(player_transl);

    if(player_transl != vec2::zero)
    {
      if(p_ddraw_enabled)
      {
        p_owner->m_world_ddraw.lines.add_arrow(
          player_old_pos, player_transl / dt, vec4mk(1.0f, 0.0f, 0.0f, 1.0f));

        p_owner->m_world_ddraw.points.add_point(
          player_old_pos, vec4mk(0.0f, 0.0f, 1.0f, 1.0f));
      }
    }
  }

  return true;
}

void game_hack_scene::logic(space & game_space, float dt)
{
  float const bullet_movement_speed = 512.0f;

  float const enemy_seek_radius = 256.0f;
  float const enemy_movement_speed = 64.0f;

  auto * player = game_space.find_entity("player");
  if(player)
  {
    auto * player_t = player->get_component<transform_component>();

    for(auto entity_it = game_space.entity_begin();
        entity_it != game_space.entity_end();
        ++entity_it)
    {
      // Enemy seeking
      auto & curr_entity = (*entity_it).second;
      if(curr_entity->get_name() == "enemy")
      {
        auto * enemy_t = curr_entity->get_component<transform_component>();

        if(p_ddraw_enabled)
        {
          p_owner->m_world_ddraw.lines.add_circle(
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
            p_owner->m_world_ddraw.lines.add_arrow(
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

void game_hack_scene::physics(space & game_space, float dt)
{
  LE_UNUSED_VAR(dt);
  // Quick and dirty hack until actual physics is in place.
  std::vector<entity *> curr_ents;
  curr_ents.reserve(game_space.entity_num());
  for(auto entity_it = game_space.entity_begin();
      entity_it != game_space.entity_end();
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
      if(!ent_outer || !ent_inner)
      {
        continue;
      }

      auto * ent_outer_t = ent_outer->get_component<transform_component>();
      auto * ent_inner_t = ent_inner->get_component<transform_component>();

      auto * ent_outer_sprite = ent_outer->get_component<sprite_component>();
      auto * ent_inner_sprite = ent_inner->get_component<sprite_component>();

      float const ent_outer_radius =
        ent_outer_t->get_scale_x() * ent_outer_sprite->get_dimensions().x() * 0.5f;

      float const ent_inner_radius =
        ent_inner_t->get_scale_x() * ent_inner_sprite->get_dimensions().x() * 0.5f;

      float const dist_sq =
        length_sq(ent_inner_t->get_pos() - ent_outer_t->get_pos());
      float const r_sum = ent_outer_radius + ent_inner_radius;

      if(p_ddraw_enabled)
      {
        p_owner->m_world_ddraw.lines.add_circle(
          ent_inner_t->get_pos(),
          ent_inner_radius,
          vec4mk(1.0f, 1.0f, 1.0f, 1.0f));
        p_owner->m_world_ddraw.lines.add_circle(
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

bool game_hack_scene::update(space & game_space, float dt)
{
  if(input(game_space, dt) == false)
  {
    return false;
  }

  logic(game_space, dt);
  physics(game_space, dt);

  //p_perf_vis.draw(p_hud_ddraw, p_profiling_records);

  return true;
}

} // namespace LE
