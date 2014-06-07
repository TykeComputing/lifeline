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
graphics_component_hack::graphics_component_hack()
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

graphics_component_hack::graphics_component_hack(vec4 const& color) :
  graphics_component_hack()
{
  m_color = color;
}

graphics_component_hack::graphics_component_hack(vec4 && color) :
  graphics_component_hack()
{
  m_color = std::move(color);
}

void graphics_component_hack::bind() const
{
  LE::vertex_array::bind(p_VAO);
}
   
void graphics_component_hack::unbind() const
{
  LE::vertex_array::unbind();
}

GLsizei graphics_component_hack::get_num_verts() const
{
  return num_verts;
}

//////////////////////////////////////////////////////////////////////////
entity_hack::entity_hack(std::string const& name) :
  entity_hack(name.c_str()) // TODO - Change
{

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
  std::vector<std::unique_ptr<shader>> shaders;
  shaders.reserve(2);
  shaders.emplace_back(std::make_unique<shader>(
    GL_VERTEX_SHADER, std::vector<std::string>(1, game_engine.get_resource_dir() + "shaders/solid_color.vert") ));
  shaders.emplace_back(std::make_unique<shader>(
    GL_FRAGMENT_SHADER, std::vector<std::string>(1, game_engine.get_resource_dir() + "shaders/solid_color.frag") ));

  // Load shader_program
  std::vector<shader *> shader_prog_input({ shaders[0].get(), shaders[1].get() });
  p_shader_prog = std::move(std::make_unique<shader_program>(shader_prog_input));
 
  shaders.clear();
  LE::shader_program::use(*p_shader_prog);
  
  {
    auto * new_ent = create_entity("player");
    new_ent->m_pos.set(0.0f, 0.5f);
    new_ent->m_g_comp.m_color.set(0.0f, 1.0f, 0.0f, 1.0f);
  }
  {
    auto * new_ent = create_entity("enemy");
    new_ent->m_pos.set(0.5f, -0.5f);
    new_ent->m_g_comp.m_color.set(1.0f, 0.0f, 0.0f, 1.0f);
  }
  {
    auto * new_ent = create_entity("enemy");
    new_ent->m_pos.set(-0.5f, -0.5f);
    new_ent->m_g_comp.m_color.set(1.0f, 0.0f, 0.0f, 1.0f);
  }
}

game_hack::~game_hack()
{
}

entity_hack * game_hack::create_entity(std::string const& name)
{
  p_entities.emplace_back(std::make_unique<entity_hack>(name));
  return p_entities.back().get();
}

entity_hack * game_hack::find_entity(std::string const& name)
{
  for(auto & it : p_entities)
  {
    if(it->m_name == name)
    {
      return it.get();
    }
  }

  return nullptr;
}

void game_hack::kill_entity(entity_hack * target)
{
  auto enemy_find_it = std::find(p_entities.begin(), p_entities.end(), target);
  if(enemy_find_it != p_entities.end())
  {
    p_entities.erase(enemy_find_it);
  }
}

bool game_hack::update(float dt)
{
  //////////////////////////////////////////////////////////////////////////
  // UPDATE
  entity_hack * player = find_entity("player");
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
          auto * new_bullet = create_entity("bullet");
          new_bullet->m_pos = player->m_pos;
          new_bullet->m_scale.set(0.05f, 0.05f);
          new_bullet->m_g_comp.m_color.set(1.0f, 0.5f, 0.0f, 1.0f);
        }

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

  // 1 = key pressed, 0 = key not pressed
  if(SDL_keys[SDL_SCANCODE_W])
  {    
    player->m_pos.y += player_movement_speed * dt;
    LE_printf("Curr y pos = %f\n", player->m_pos.y);
  }
  if(SDL_keys[SDL_SCANCODE_S])
  {
    player->m_pos.y -= player_movement_speed * dt;
  }
  if(SDL_keys[SDL_SCANCODE_A])
  {
    player->m_pos.x -= player_movement_speed * dt;
  }
  if(SDL_keys[SDL_SCANCODE_D])
  {
    player->m_pos.x += player_movement_speed * dt;
  }

  for(auto & entity_it : p_entities)
  {
    if(entity_it->m_name == "enemy")
    {
      vec2 dir_to_player = player->m_pos - entity_it->m_pos; LE_UNUSED_VAR(dir_to_player);
      float dist_to_player = dir_to_player.normalize();
      if(dist_to_player <= enemy_seek_radius)
      {
        entity_it->m_pos += dir_to_player * enemy_movement_speed * dt;      
      }
    }
    else if(entity_it->m_name == "bullet")
    {
      // TODO velocity
      entity_it->m_pos.y -= bullet_movement_speed * dt;      
    }
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
    mat3 model_to_world
    {
      entity_it->m_scale.x, 0.0f, entity_it->m_pos.x,
      0.0f, entity_it->m_scale.y, entity_it->m_pos.y,
      0.0f, 0.0f, 1.0f  // TODO: mat2x3 instead?
    };

    auto const& curr_g_comp = entity_it->m_g_comp;
    glUniform4fv(color_ul, 1, curr_g_comp.m_color.v);

    glUniformMatrix3fv(model_to_world_ul, 1, GL_TRUE, model_to_world.a);

    curr_g_comp.bind();
    LE::vertex_buffer::draw_arrays(GL_TRIANGLES, 0, curr_g_comp.get_num_verts());
    curr_g_comp.unbind();
  }
}

} // namespace LE
