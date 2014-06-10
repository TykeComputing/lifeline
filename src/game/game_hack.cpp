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
#include <common/resource_exception.h>
#include <graphics/vertex.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>
#include <engine/engine.h>
#include <common/LE_printf.h>

namespace LE
{

//////////////////////////////////////////////////////////////////////////
sprite_component_hack::sprite_component_hack()
{
  LE::vertex_array::bind(p_VAO);
  LE::vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);

  vertex::specify_vertex_attributes();
  vertex verts[] =
  {
    { { -0.5f, -0.5f }, { 0.0f, 0.0f } },
    { {  0.5f, -0.5f }, { 1.0f, 0.0f } },
    { { -0.5f,  0.5f }, { 0.0f, 1.0f } },

    { { -0.5f,  0.5f }, { 0.0f, 1.0f } },
    { {  0.5f, -0.5f }, { 1.0f, 0.0f } },
    { {  0.5f,  0.5f }, { 1.0f, 1.0f } }
  };
  num_verts = sizeof(verts) / sizeof(vertex);

  LE::vertex_buffer::set_data(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  LE::vertex_array::unbind();
}

sprite_component_hack::sprite_component_hack(vec4 const& color) :
  sprite_component_hack()
{
  m_color = color;
}

sprite_component_hack::sprite_component_hack(vec4 && color) :
  sprite_component_hack()
{
  m_color = std::move(color);
}

void sprite_component_hack::bind() const
{
  LE::vertex_array::bind(p_VAO);
}

void sprite_component_hack::unbind() const
{
  LE::vertex_array::unbind();
}

GLsizei sprite_component_hack::get_num_verts() const
{
  return num_verts;
}

//////////////////////////////////////////////////////////////////////////
entity_hack::entity_hack(std::string const& name) :
  entity_hack(name.c_str()) // TODO - Change
{
  static unique_id_gen id_gen;
  m_id = id_gen.generate();
}

entity_hack::entity_hack(char const* name) :
  m_name(name)
{

}

//////////////////////////////////////////////////////////////////////////
game_hack::game_hack(engine & game_engine)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // TODO - Move shader loading to someplace that makes more sense once resources exist
  // Load shaders
  std::vector<std::shared_ptr<shader>> shaders;
  shaders.reserve(2);
  shaders.emplace_back(std::make_shared<shader>(
    GL_VERTEX_SHADER, std::vector<std::string>(1, game_engine.get_resource_dir() + "shaders/solid_color.vert") ));
  shaders.emplace_back(std::make_shared<shader>(
    GL_FRAGMENT_SHADER, std::vector<std::string>(1, game_engine.get_resource_dir() + "shaders/solid_color.frag") ));

  // Load shader_program
  std::vector<shader *> shader_prog_input({ shaders[0].get(), shaders[1].get() });
  p_shader_prog = std::unique_ptr<shader_program>{new shader_program{shader_prog_input}};

  shaders.clear();
  LE::shader_program::use(*p_shader_prog);

  {
    auto new_ent_ref = create_entity("player");
    auto new_ent = new_ent_ref.lock();
    new_ent->m_pos.set({0.0f, 0.5f});
    new_ent->m_gfx_comp.m_color.set({0.0f, 1.0f, 0.0f, 1.0f});
  }
  {
    auto new_ent_ref = create_entity("enemy");
    auto new_ent = new_ent_ref.lock();
    new_ent->m_pos.set({0.5f, -0.5f});
    new_ent->m_gfx_comp.m_color.set({1.0f, 0.0f, 0.0f, 1.0f});
  }
  {
    auto new_ent_ref = create_entity("enemy");
    auto new_ent = new_ent_ref.lock();
    new_ent->m_pos.set({-0.5f, -0.5f});
    new_ent->m_gfx_comp.m_color.set({1.0f, 0.0f, 0.0f, 1.0f});
  }
}

game_hack::~game_hack()
{
}

std::weak_ptr<entity_hack> game_hack::create_entity(std::string const& name)
{
  auto new_ent = std::make_shared<entity_hack>(name);
  p_entities.emplace(std::make_pair(new_ent->m_id, new_ent));
  return new_ent;
}

std::weak_ptr<entity_hack> game_hack::find_entity(std::string const& name)
{
  for(auto & it : p_entities)
  {
    if(it.second->m_name == name)
    {
      return it.second;
    }
  }

  return {};
}

void game_hack::kill_entity(std::weak_ptr<entity_hack> target)
{
  auto owned_target = target.lock();
  if(owned_target)
  {
    auto enemy_find_it = p_entities.find(owned_target->m_id);
    if(enemy_find_it != p_entities.end())
    {
      p_entities.erase(enemy_find_it);
    }
  }
}

bool game_hack::update(float dt)
{
  //////////////////////////////////////////////////////////////////////////
  // UPDATE
  auto player_ref = find_entity("player");
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
            auto new_bullet_ref = create_entity("bullet");
            auto new_bullet = new_bullet_ref.lock();
            new_bullet->m_pos = player->m_pos;
            new_bullet->m_scale.set({0.05f, 0.05f});
            new_bullet->m_gfx_comp.m_color.set({1.0f, 0.5f, 0.0f, 1.0f});
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
    // 1 = key pressed, 0 = key not pressed
    if(SDL_keys[SDL_SCANCODE_W])
    {
      player->m_pos[1] += player_movement_speed * dt;
    }
    if(SDL_keys[SDL_SCANCODE_S])
    {
      player->m_pos[1] -= player_movement_speed * dt;
    }
    if(SDL_keys[SDL_SCANCODE_A])
    {
      player->m_pos[0] -= player_movement_speed * dt;
    }
    if(SDL_keys[SDL_SCANCODE_D])
    {
      player->m_pos[0] += player_movement_speed * dt;
    }

    // Enemy seeking
    for(auto & entity_it : p_entities)
    {
      auto & curr_entity = entity_it.second;
      if(curr_entity->m_name == "enemy")
      {
        vec2 dir_to_player = player->m_pos - curr_entity->m_pos;
        float dist_to_player;
        normalize(dir_to_player, dist_to_player);
        if(dist_to_player <= enemy_seek_radius)
        {
          curr_entity->m_pos += dir_to_player * enemy_movement_speed * dt;
        }
      }
      else if(curr_entity->m_name == "bullet")
      {
        // TODO velocity
        curr_entity->m_pos[1] -= bullet_movement_speed * dt;
      }
    }
  }

  std::vector<std::weak_ptr<entity_hack>> ents_to_kill;

  // Quick and oh so dirty hack, going to unhack soon anyway, just need to get compiling on
  //   GCC.
  std::vector<std::weak_ptr<entity_hack>> curr_ents;
  curr_ents.reserve(p_entities.size());
  for(auto & ent_it : p_entities)
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

      float dist_sq = length_sq(ent_inner->m_pos - ent_outer->m_pos);
      float r_sum = ent_outer->m_scale[0] + ent_inner->m_scale[0];
      r_sum *= 0.5f; // use half of scale as radius
      float r_sum_sq = r_sum * r_sum;
      if(dist_sq <= r_sum_sq)
      {
        std::shared_ptr<entity_hack> * ents[2] = { &ent_outer, &ent_inner };
        entity_hack * ents_raw[2] = { ents[0]->get(), ents[1]->get() };

        auto ent_involved_in_collision =
          [](std::string const& name,
            entity_hack * (&ents_raw)[2],
            unsigned & index,
            unsigned & other_index)->bool
        {
          if(ents_raw[0]->m_name == name)
          {
            index = 0;
            other_index = 1;
            return true;
          }
          else if(ents_raw[1]->m_name == name)
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
          if(ents_raw[other_index]->m_name == "enemy")
          {
            ents_to_kill.emplace_back(*ents[index]);
          }
        }
        if(ent_involved_in_collision("enemy", ents_raw, index, other_index))
        {
          if(ents_raw[other_index]->m_name == "bullet")
          {
            ents_to_kill.emplace_back(*ents[index]);
            ents_to_kill.emplace_back(*ents[other_index]);
          }
        }
      }
    }
  }

  for(auto const& kill_it : ents_to_kill)
  {
    kill_entity(kill_it);
  }

  return true;
}

void game_hack::draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  GLint color_ul = p_shader_prog->get_unform_location("color");
  GLint model_to_world_ul = p_shader_prog->get_unform_location("model_to_world");

  // Terrible game loop, HACK HACK HACK
  for(auto & entity_it : p_entities)
  {
    auto & curr_ent = entity_it.second;
    mat3 model_to_world
    {
      curr_ent->m_scale[0], 0.0f, curr_ent->m_pos[0],
      0.0f, curr_ent->m_scale[1], curr_ent->m_pos[1],
      0.0f, 0.0f, 1.0f  // TODO: mat2x3 instead?
    };

    auto const& curr_g_comp = curr_ent->m_gfx_comp;
    glUniform4fv(color_ul, 1, curr_g_comp.m_color.data);

    glUniformMatrix3fv(model_to_world_ul, 1, GL_TRUE, model_to_world.a);

    curr_g_comp.bind();
    LE::vertex_buffer::draw_arrays(GL_TRIANGLES, 0, curr_g_comp.get_num_verts());
    curr_g_comp.unbind();
  }
}

} // namespace LE
