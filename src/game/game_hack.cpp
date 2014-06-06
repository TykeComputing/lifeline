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

void graphics_component_hack::bind()
{
  LE::vertex_array::bind(p_VAO);
}
   
void graphics_component_hack::unbind()
{
  LE::vertex_array::unbind();
}

GLsizei graphics_component_hack::get_num_verts() const
{
  return num_verts;
}

//////////////////////////////////////////////////////////////////////////
entity_hack::entity_hack(std::string const& name, float health, vec4 const& color, vec2 const& pos, vec2 const& scale) :
  m_name(name), m_health(health), m_pos(pos), m_scale(scale),
  m_g_comp(color)
{

}

entity_hack::entity_hack(std::string && name, float health, vec4 && color, vec2 && pos, vec2 && scale) :
  m_name(std::move(name)), m_health(health), m_pos(std::move(pos)), m_scale(std::move(scale)),
  m_g_comp(color)
{

}

//////////////////////////////////////////////////////////////////////////
game_hack::game_hack() :
  p_player()
{
  auto lvalue = vec4{ 0.0f, 1.0f, 0.0f, 1.0f };
  p_enemies.emplace_back(std::make_unique<entity_hack>(std::string("lvaluetest"), 100.0f, lvalue, vec2{ 0.0f, 0.0f }, vec2{ 0.1f, 0.1f }));
  p_enemies.emplace_back(std::make_unique<entity_hack>(std::string("player"), 100.0f, vec4{ 0.0f, 1.0f, 0.0f, 1.0f }, vec2{ 0.0f, 0.0f }, vec2{ 0.1f, 0.1f }));
  p_enemies.emplace_back(std::make_unique<entity_hack>(std::string("enemy"),   50.0f, vec4{ 1.0f, 0.0f, 0.0f, 1.0f }, vec2{ 0.0f, 0.0f }, vec2{ 0.1f, 0.1f }));
  p_enemies.emplace_back(std::make_unique<entity_hack>(std::string("enemy"),   50.0f, vec4{ 1.0f, 0.0f, 0.0f, 1.0f }, vec2{ 0.0f, 0.0f }, vec2{ 0.1f, 0.1f }));
}


game_hack::~game_hack()
{
}

void game_hack::update()
{
  
  
  //LE::vertex_buffer::draw_arrays(GL_TRIANGLES, 0, g_comp.get_num_verts());
}

void game_hack::kill_player()
{
  p_player.reset(nullptr);
}

void game_hack::kill_enemy(std::unique_ptr<entity_hack> const& enemy)
{
  auto enemy_find_it = std::find(p_enemies.begin(), p_enemies.end(), enemy);
  if(enemy_find_it != p_enemies.end())
  {
    p_enemies.erase(enemy_find_it);
  }
}

} // namespace LE
