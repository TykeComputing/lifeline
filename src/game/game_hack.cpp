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
#include <common/profiling.h>
#include <common/resource_exception.h>

#include <engine/engine.h>
#include <engine/space.h>
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
game_hack::game_hack(engine & game_engine, space & game_space) :
  p_engine(game_engine)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glLineWidth(2.0f);
  glPointSize(5.0f);

  p_profiling_records.set_max_num_record_entries(600);

  p_perf_vis.set_label_color("graphics", vec4(1.0f, 0.0f, 0.0f, 1.0f));
  p_perf_vis.set_label_color("physics", vec4(1.0f, 1.0f, 0.0f, 1.0f));
  p_perf_vis.set_label_color("physics", vec4(0.0f, 0.0f, 1.0f, 1.0f));
  p_perf_vis.set_label_color("update_total", vec4(0.0f, 1.0f, 0.0f, 1.0f));

  // TODO - Move shader loading to someplace that makes more sense once resources exist
  // Load shaders

  load_shader(
    p_textured_shader_prog,
    "shaders/2D/textured.vert",
    "shaders/2D/textured.frag");
  load_shader(
    p_debug_shader_prog,
    "shaders/2D/debug_draw.vert",
    "shaders/2D/debug_draw.frag");

  {
    auto * new_ent = game_space.create_entity("player");
    new_ent->get_component<transform_component>()->set_pos(0.0f, 0.5f);
    new_ent->get_component<sprite_component>()->m_color.set(0.0f, 1.0f, 0.0f, 1.0f);
  }

  {
    auto * new_ent = game_space.create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(0.5f, -0.5f);
    new_ent->get_component<sprite_component>()->m_color.set(1.0f, 0.0f, 0.0f, 1.0f);
  }
  {
    auto * new_ent = game_space.create_entity("enemy");
    new_ent->get_component<transform_component>()->set_pos(-0.5f, -0.5f);
    new_ent->get_component<sprite_component>()->m_color.set(1.0f, 0.0f, 0.0f, 1.0f);
  }
}

game_hack::~game_hack()
{
}

void game_hack::load_shader(
  std::unique_ptr<shader_program> & out_sp,
  char const* vert,
  char const* frag)
{
  log_status(log_scope::GAME, "Attempting to load shaders \"{}\" and \"{}\"", vert, frag);

  try
  {
    std::vector<std::shared_ptr<shader>> shaders;
    shaders.reserve(2);
    shaders.emplace_back(std::make_shared<shader>(
      GL_VERTEX_SHADER, std::vector<std::string>(1, p_engine.get_resource_dir() + vert) ));
    shaders.emplace_back(std::make_shared<shader>(
      GL_FRAGMENT_SHADER, std::vector<std::string>(1, p_engine.get_resource_dir() + frag) ));

    // Load shader_program
    std::vector<shader *> shader_prog_input({ shaders[0].get(), shaders[1].get() });
    out_sp = std::unique_ptr<shader_program>{new shader_program{shader_prog_input}};
  }
  catch(LE::resource_exception const& e)
  {
    log_error(log_scope::GAME, "{}", e.what());
    LE_FATAL_ERROR("Error loading shader!");
    return;
  }
}

// returns false if a quit message has been received
bool game_hack::input(space & game_space, float dt)
{
  profiling_point<> pp(p_profiling_records, "input");

  float const player_movement_speed = 0.8f;

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
            new_bullet_t->set_scale(0.05f, 0.05f);
            new_bullet->get_component<sprite_component>()->m_color.set(1.0f, 0.5f, 0.0f, 1.0f);
          }
        }
        break;

        // Shader reloading
        case SDLK_RETURN:
        {
          load_shader(
            p_textured_shader_prog,
            "shaders/2D/textured.vert",
            "shaders/2D/textured.frag");
          load_shader(
            p_debug_shader_prog,
            "shaders/2D/debug_draw.vert",
            "shaders/2D/debug_draw.frag");
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
    player_t->translate(player_transl);

    if(player_transl != zero_vec2)
    {
      p_world_ddraw.lines.add_arrow(
        player_old_pos, player_transl / dt, vec4mk(1.0f, 0.0f, 0.0f, 1.0f));

      p_world_ddraw.points.add_point(
        player_old_pos, vec4mk(0.0f, 0.0f, 1.0f, 1.0f));
    }
  }

  return true;
}

void game_hack::logic(space & game_space, float dt)
{
  profiling_point<> pp(p_profiling_records, "logic");

  float const bullet_movement_speed = 2.0f;

  float const enemy_seek_radius = 1.0f;
  float const enemy_movement_speed = 0.4f;

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

        p_world_ddraw.lines.add_circle(
          enemy_t->get_pos(), enemy_seek_radius, vec4mk(1.0f, .0f, 1.0f, 1.0f));

        vec2 dir_to_player =
            player_t->get_pos() - enemy_t->get_pos();
        float dist_to_player;
        normalize(dir_to_player, dist_to_player);

        if(dist_to_player <= enemy_seek_radius)
        {
          enemy_t->translate(dir_to_player * enemy_movement_speed * dt);

          p_world_ddraw.lines.add_arrow(
            enemy_t->get_pos(), dir_to_player, enemy_seek_radius, vec4mk(1.0f, 0.0f, 1.0f, 1.0f));
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

void game_hack::physics(space & game_space, float dt)
{
  profiling_point<> pp(p_profiling_records, "physics");

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

      float dist_sq =
          length_sq(ent_inner_t->get_pos() - ent_outer_t->get_pos());
      float r_sum =
          ent_outer_t->get_scale_x() + ent_inner_t->get_scale_x();
      r_sum *= 0.5f; // use half of scale as radius

      p_world_ddraw.lines.add_circle(
        ent_inner_t->get_pos(),
        ent_inner_t->get_scale_x() * 0.5f,
        vec4mk(1.0f, 1.0f, 1.0f, 1.0f));
      p_world_ddraw.lines.add_circle(
        ent_outer_t->get_pos(),
        ent_outer_t->get_scale_x() * 0.5f,
        vec4mk(1.0f, 1.0f, 1.0f, 1.0f));

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

bool game_hack::update(space & game_space, float dt)
{
  p_profiling_records.start_new_record_entry();

  profiling_point<> pp(p_profiling_records, "update_total");

  p_world_ddraw.clear();
  p_world_ddraw.clear();
  p_hud_ddraw.clear();

  if(input(game_space, dt) == false)
  {
    return false;
  }

  logic(game_space, dt);
  physics(game_space, dt);

  p_perf_vis.draw(p_hud_ddraw, p_profiling_records);

  return true;
}

void game_hack::draw(space & game_space)
{
  profiling_point<> pp(p_profiling_records, "graphics");

  LE::shader_program::use(*p_textured_shader_prog);

  glClear(GL_COLOR_BUFFER_BIT);

  GLint color_multiplier_ul = p_textured_shader_prog->get_unform_location("color_multiplier");
  GLint texture_ul = p_textured_shader_prog->get_unform_location("texture");
  GLint model_to_world_ul = p_textured_shader_prog->get_unform_location("model_to_world");

  texture::set_active_unit(0);
  glUniform1i(texture_ul, 0);

  LE_FATAL_ERROR_IF_GL_ERROR();

  // Terrible draw loop, HACK HACK HACK
  for(auto entity_it = game_space.entity_begin();
    entity_it != game_space.entity_end();
    ++entity_it)
  {
    auto & curr_ent = (*entity_it).second;
    auto const* curr_ent_t = curr_ent->get_component<transform_component>();
    auto const& model_to_world = curr_ent_t->get_matrix();

    auto const* curr_g_comp = curr_ent->get_component<sprite_component>();
    glUniform4fv(color_multiplier_ul, 1, curr_g_comp->m_color.data);

    glUniformMatrix3fv(model_to_world_ul, 1, GL_TRUE, model_to_world.data);

    LE_FATAL_ERROR_IF_GL_ERROR();
    curr_g_comp->bind();
    LE_FATAL_ERROR_IF_GL_ERROR();
    LE::vertex_buffer::draw_arrays(GL_TRIANGLES, 0, curr_g_comp->get_num_verts());
    LE_FATAL_ERROR_IF_GL_ERROR();
    curr_g_comp->unbind();
    LE_FATAL_ERROR_IF_GL_ERROR();

    LE_FATAL_ERROR_IF_GL_ERROR();

    // TODO - REMOVE
    p_world_ddraw.lines.add_transform(curr_ent_t->get_matrix(), 0.1f);
  }
  LE_FATAL_ERROR_IF_GL_ERROR();

  LE::shader_program::use(*p_debug_shader_prog);

  // TODO: Use camera mat
  p_world_ddraw.draw();
  p_world_ddraw.draw();

  // TODO: Use hud mat
  p_hud_ddraw.draw();

  LE::shader_program::use_default();

  LE_FATAL_ERROR_IF_GL_ERROR();
}

} // namespace LE
