/*
************************************************************************************************
Copyright 2014 Peter Clark

This file is part of Lifeline Engine.

Lifeline Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Lifeline Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Lifeline Engine.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************************
*/

#include "game_hack.h"

#include <common/fatal_construction_exception.h>

#include <graphics/shader_program.h>
#include <string>
#include <vector>
#include <common/fatal_error.h>
#include <common/logging.h>
#include <common/resource_exception.h>
#include <graphics/vertex.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>
#include <engine/engine.h>
#include <engine/transform_component.h>

#include <engine/sprite_component.h>
#include <engine/transform_component.h>

namespace LE
{

//////////////////////////////////////////////////////////////////////////
game_hack::game_hack(engine & game_engine)
{
  auto & ent_mgr = game_engine.get_entity_mgr();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // TODO - Move shader loading to someplace that makes more sense once resources exist
  // Load shaders

  load_shader(game_engine, p_shader_prog, "shaders/solid_color.vert", "shaders/solid_color.frag");
  load_shader(game_engine, p_debug_shader_prog, "shaders/debug_draw.vert", "shaders/debug_draw.frag");

  {
    auto new_ent_ref = ent_mgr.create_entity("player");
    auto new_ent = new_ent_ref.lock();
    new_ent->get_component<transform_component>()->set_pos(0.0f, 0.5f);
    new_ent->get_component<sprite_component>()->m_color.set({0.0f, 1.0f, 0.0f, 1.0f});
  }

  {
    auto new_ent_ref = ent_mgr.create_entity("enemy");
    auto new_ent = new_ent_ref.lock();
    new_ent->get_component<transform_component>()->set_pos(0.5f, -0.5f);
    new_ent->get_component<sprite_component>()->m_color.set({1.0f, 0.0f, 0.0f, 1.0f});
  }
  {
    auto new_ent_ref = ent_mgr.create_entity("enemy");
    auto new_ent = new_ent_ref.lock();
    new_ent->get_component<transform_component>()->set_pos(-0.5f, -0.5f);
    new_ent->get_component<sprite_component>()->m_color.set({1.0f, 0.0f, 0.0f, 1.0f});
  }

  glLineWidth(2.0f);
  glPointSize(5.0f);
}

game_hack::~game_hack()
{
}

void game_hack::load_shader(
  engine & game_engine,
  std::unique_ptr<shader_program> & out_sp,
  char const* vert,
  char const* frag)
{
  try
  {
    LE_FATAL_ERROR_IF(out_sp != nullptr, "Attempting to load existing shader!");

    std::vector<std::shared_ptr<shader>> shaders;
    shaders.reserve(2);
    shaders.emplace_back(std::make_shared<shader>(
      GL_VERTEX_SHADER, std::vector<std::string>(1, game_engine.get_resource_dir() + vert) ));
    shaders.emplace_back(std::make_shared<shader>(
      GL_FRAGMENT_SHADER, std::vector<std::string>(1, game_engine.get_resource_dir() + frag) ));

    // Load shader_program
    std::vector<shader *> shader_prog_input({ shaders[0].get(), shaders[1].get() });
    out_sp = std::unique_ptr<shader_program>{new shader_program{shader_prog_input}};
  }
  catch(LE::resource_exception const& e)
  {
    log_error(log_scope::GAME, "{}") << e.what();
    LE_FATAL_ERROR("Error loading shader!");
    return;
  }
}

bool game_hack::update(engine & game_engine, float dt)
{
  p_line_drawer.clear();
  p_point_drawer.clear();

  auto & ent_mgr = game_engine.get_entity_mgr();

  //////////////////////////////////////////////////////////////////////////
  // UPDATE
  auto player_ref = ent_mgr.find_entity("player");
  auto player = player_ref.lock();

  float const player_movement_speed = 0.8f;
  float const bullet_movement_speed = 2.0f;

  float const enemy_seek_radius = 1.0f;
  float const enemy_movement_speed = 0.4f;

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

            auto new_bullet_ref = ent_mgr.create_entity("bullet");
            auto new_bullet = new_bullet_ref.lock();
            auto * new_bullet_t = new_bullet->get_component<transform_component>();
            new_bullet_t->set_pos(player_t->get_pos());
            new_bullet_t->set_scale(0.05f, 0.05f);
            new_bullet->get_component<sprite_component>()->m_color.set({1.0f, 0.5f, 0.0f, 1.0f});
          }
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

    case SDL_KEYUP:
    {
      //switch(curr_event.key.keysym.sym)
      //{


      //}
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
    vec2 player_transl = zero_vec2;
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
    player->get_component<transform_component>()->translate(player_transl);

    if(player_transl != zero_vec2)
    {
      p_line_drawer.add_arrow(
        player_old_pos, player_transl / dt, vec4({1.0f, 0.0f, 0.0f, 1.0f}));

      p_line_drawer.add_aabb(
        vec2({-0.9f, -0.9f}), vec2({0.9f, 0.9f}), vec4({1.0f, 1.0f, 0.0f, 1.0f}));

      p_point_drawer.add_point(
        player_old_pos, vec4({0.0f, 0.0f, 1.0f, 1.0f}));
    }

    for(auto & entity_it : ent_mgr.p_entities)
    {
      // Enemy seeking
      auto & curr_entity = entity_it.second;
      if(curr_entity->get_name() == "enemy")
      {
        auto * enemy_t = curr_entity->get_component<transform_component>();

        p_line_drawer.add_circle(
          enemy_t->get_pos(), enemy_seek_radius, vec4({1.0f, .0f, 1.0f, 1.0f}));

        vec2 dir_to_player =
            player_t->get_pos() - enemy_t->get_pos();
        float dist_to_player;
        normalize(dir_to_player, dist_to_player);

        if(dist_to_player <= enemy_seek_radius)
        {
          enemy_t->translate(dir_to_player * enemy_movement_speed * dt);

          p_line_drawer.add_arrow(
            enemy_t->get_pos(), dir_to_player, enemy_seek_radius, vec4({1.0f, 0.0f, 1.0f, 1.0f}));
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

  // Quick and oh so dirty hack, going to unhack soon anyway, just need to get compiling on
  //   GCC.
  std::vector<std::weak_ptr<entity>> curr_ents;
  curr_ents.reserve(ent_mgr.p_entities.size());
  for(auto & ent_it : ent_mgr.p_entities)
  {
    curr_ents.emplace_back(ent_it.second);
  }

  // TODO - Stick to actual naming conventions when unhacking this
  // n^2 collision detection using circles based on pos/scale
  for(auto ent_outer_it = curr_ents.begin(); ent_outer_it != curr_ents.end(); ++ent_outer_it)
  {
    // Don't consider this object or ones before it for testing (they've already been tested).
    for(auto ent_inner_it = curr_ents.begin() + 1; ent_inner_it != curr_ents.end(); ++ent_inner_it)
    {
      auto ent_outer = (*ent_outer_it).lock();
      auto ent_inner = (*ent_inner_it).lock();
      if(!ent_outer || !ent_inner)
      {
        continue;
      }

      auto * ent_outer_t = ent_outer->get_component<transform_component>();
      auto * ent_inner_t = ent_inner->get_component<transform_component>();

      float dist_sq =
          length_sq(ent_inner_t->get_pos() - ent_outer_t->get_pos());
      float r_sum =
          ent_outer_t->get_scale_x() + ent_inner_t->get_scale_x();
      r_sum *= 0.5f; // use half of scale as radius

      p_line_drawer.add_circle(
        ent_inner_t->get_pos(),
        ent_inner_t->get_scale_x() * 0.5f,
        vec4({1.0f, 1.0f, 1.0f, 1.0f}));
      p_line_drawer.add_circle(
        ent_outer_t->get_pos(),
        ent_outer_t->get_scale_x() * 0.5f,
        vec4({1.0f, 1.0f, 1.0f, 1.0f}));

      float r_sum_sq = r_sum * r_sum;
      if(dist_sq <= r_sum_sq)
      {
        std::shared_ptr<entity> * ents[2] = { &ent_outer, &ent_inner };
        entity * ents_raw[2] = { ents[0]->get(), ents[1]->get() };

        auto ent_involved_in_collision =
          [](std::string const& name,
            entity * (&ents_raw)[2],
            unsigned & index,
            unsigned & other_index)->bool
        {
          if(ents_raw[0]->get_name() == name)
          {
            index = 0;
            other_index = 1;
            return true;
          }
          else if(ents_raw[1]->get_name() == name)
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
        if(ent_involved_in_collision("player", ents_raw, index, other_index))
        {
          if(ents_raw[other_index]->get_name() == "enemy")
          {
            (*ents[index])->kill();
          }
        }
        if(ent_involved_in_collision("enemy", ents_raw, index, other_index))
        {
          if(ents_raw[other_index]->get_name() == "bullet")
          {
            (*ents[index])->kill();
            (*ents[other_index])->kill();
          }
        }
      }
    }
  }

  return true;
}

void game_hack::draw(engine & game_engine)
{
  LE::shader_program::use(*p_shader_prog);

  auto & ent_mgr = game_engine.get_entity_mgr();

  glClear(GL_COLOR_BUFFER_BIT);

  GLint color_ul = p_shader_prog->get_unform_location("color");
  GLint model_to_world_ul = p_shader_prog->get_unform_location("model_to_world");

  // Terrible game loop, HACK HACK HACK
  for(auto & entity_it : ent_mgr.p_entities)
  {
    auto & curr_ent = entity_it.second;
    auto const* curr_ent_t = curr_ent->get_component<transform_component>();
    auto const& model_to_world = curr_ent_t->get_matrix();

    auto const* curr_g_comp = curr_ent->get_component<sprite_component>();
    glUniform4fv(color_ul, 1, curr_g_comp->m_color.data);

    glUniformMatrix3fv(model_to_world_ul, 1, GL_TRUE, model_to_world.data);

    curr_g_comp->bind();
    LE::vertex_buffer::draw_arrays(GL_TRIANGLES, 0, curr_g_comp->get_num_verts());
    curr_g_comp->unbind();

    // TODO - REMOVE
    p_line_drawer.add_transform(curr_ent_t->get_matrix(), 0.1f);
  }

  LE::shader_program::use(*p_debug_shader_prog);

  p_line_drawer.draw();
  p_point_drawer.draw();

  LE::shader_program::use_default();
}

} // namespace LE
