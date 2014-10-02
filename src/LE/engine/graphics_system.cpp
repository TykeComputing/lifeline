/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "graphics_system.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <LE/common/logging.h>
#include <LE/common/fatal_error.h>
#include <LE/common/fatal_construction_exception.h>
#include <LE/common/resource_exception.h>
#include <LE/common/resource_manager.h>

#include <LE/graphics/colors.h>
#include <LE/graphics/error_checking.h>
#include <LE/graphics/texture.h>

#include <LE/engine/tilemap_component.h>
#include <LE/engine/transform_component.h>
#include <LE/engine/sprite_component.h>

#include <LE/math/mat.h>

namespace LE
{

graphics_system::graphics_system()
{
  // Experimental is needed for OpenGL 3.2+ core contexts
  // See: http://www.opengl.org/wiki/OpenGL_Loading_Library
  glewExperimental = GL_TRUE;
  GLenum glew_init_res = glewInit();
  if(glew_init_res != GLEW_OK)
  {
    log_error(log_scope::ENGINE, "Error intializing GLEW: {}",
      convert_unsigned_string_to_signed(glewGetErrorString(glew_init_res)));
    throw fatal_construction_exception{};
  }

  std::string glew_init_GL_errors = get_GL_errors();
  if(glew_init_GL_errors.empty())
  {
    log_status(log_scope::ENGINE, "OpenGL Function Loading: No errors on glewInit");
  }
  else
  {
    log_status(log_scope::ENGINE, "OpenGL Function Loading: Errors on glewInit: {}",
       glew_init_GL_errors.c_str());
  }

  if(!GLEW_VERSION_3_2)
  {
    log_error(log_scope::ENGINE, "Unable to obtain OpenGL 3.2 context");
    throw fatal_construction_exception{};
  }

  log_status(log_scope::ENGINE, log_line_seperator);

  log_status(log_scope::ENGINE, "Graphics Successfully Initialized");
  log_status(log_scope::ENGINE, "System OpenGL Info");
  log_status(log_scope::ENGINE, log_line_seperator_sub_1);
  log_status(log_scope::ENGINE, " Version: {}",
    convert_unsigned_string_to_signed( glGetString(GL_VERSION) ).c_str());
  log_status(log_scope::ENGINE, "  Vendor: {}",
    convert_unsigned_string_to_signed( glGetString(GL_VENDOR) ).c_str());
  log_status(log_scope::ENGINE, "Renderer: {}",
    convert_unsigned_string_to_signed( glGetString(GL_RENDERER) ).c_str());
  log_status(log_scope::ENGINE, " Shading: {}",
    convert_unsigned_string_to_signed( glGetString(GL_SHADING_LANGUAGE_VERSION) ).c_str());

  log_status(log_scope::ENGINE, log_line_seperator);

  glEnable(GL_FRAMEBUFFER_SRGB);

  p_load_shader(
    p_textured_shader_prog,
    "shaders/2D/textured.vert",
    "shaders/2D/textured.frag");
  p_load_shader(
    p_debug_shader_prog,
    "shaders/2D/debug_draw.vert",
    "shaders/2D/debug_draw.frag");

  // Set some initial OpenGL state
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glLineWidth(2.0f);
  glPointSize(5.0f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void graphics_system::clear_render_target()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void graphics_system::render(space & target)
{
  // HACK /////////////////////////////////////////

  // Camera space =
  mat3 world_to_camera({
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  });

  uvec2 render_target_half_size = p_render_target_size / 2u;

  mat3 camera_to_NDC({
    1.0f / render_target_half_size.x(), 0.0f, 0.0f,
    0.0f, 1.0f / render_target_half_size.y(), 0.0f,
    0.0f, 0.0f, 1.0f
  });

  mat3 world_to_NDC = camera_to_NDC * world_to_camera;
  /////////////////////////////////////////////////

  p_render_tilemaps(target, world_to_NDC);
  p_render_sprites(target, world_to_NDC);
  p_render_ddraw(target, world_to_NDC);

  LE::shader_program::use_default();
}

void graphics_system::update_render_target_size(uvec2 const& window_size)
{
  // Completely arbitrary at the moment. TODO - Actually implement
  uvec2 const max_render_target_size(800, 450);

  uvec2 scaled_window_size = window_size / 2u;

  for(unsigned i = 0; i < uvec2::size; ++i)
  {
    if(scaled_window_size[i] > max_render_target_size[i])
    {
      scaled_window_size[i] /= 2;
    }
  }

  p_render_target_size = scaled_window_size;

  log_status(log_scope::ENGINE, "Render target size: {}", p_render_target_size);
}

uvec2 const& graphics_system::get_render_target_size() const
{
  return p_render_target_size;
}

void graphics_system::p_load_shader(
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
      GL_VERTEX_SHADER, std::vector<std::string>(1, resource_manager::get_resource_dir() + vert) ));
    shaders.emplace_back(std::make_shared<shader>(
      GL_FRAGMENT_SHADER, std::vector<std::string>(1, resource_manager::get_resource_dir() + frag) ));

    // Load shader_program
    std::vector<shader *> shader_prog_input({ shaders[0].get(), shaders[1].get() });
    out_sp = std::unique_ptr<shader_program>{new shader_program{shader_prog_input}};
  }
  catch(LE::resource_exception const&)
  {
    LE_FATAL_ERROR("Error loading shader!");
    return;
  }
}

void graphics_system::p_render_sprites(
  space & target,
  mat3 const& world_to_NDC)
{
  LE::shader_program::use(*p_textured_shader_prog);

  GLint color_multiplier_ul = p_textured_shader_prog->get_unform_location("color_multiplier");
  GLint texture_ul = p_textured_shader_prog->get_unform_location("texture");
  GLint to_NDC_ul = p_textured_shader_prog->get_unform_location("to_NDC");

  texture::set_active_unit(0);
  glUniform1i(texture_ul, 0);

  for(auto sprite_comp_it = target.engine_component_begin<sprite_component>();
    sprite_comp_it != target.engine_component_end<sprite_component>();
    ++sprite_comp_it)
  {
    sprite_component const* curr_sprite_comp =
      static_cast<sprite_component const*>(*sprite_comp_it);
    auto const* curr_ent = curr_sprite_comp->get_owning_entity();
    auto const* curr_ent_t = curr_ent->get_component<transform_component>();

    auto const& model_to_world = curr_ent_t->get_matrix();

    glUniform4fv(color_multiplier_ul, 1, curr_sprite_comp->m_color.data);

    mat3 model_to_NDC = world_to_NDC * model_to_world;
    glUniformMatrix3fv(to_NDC_ul, 1, GL_TRUE, model_to_NDC.data);

    curr_sprite_comp->bind();
    renderable_array_buffer::draw(GL_TRIANGLES, 0, curr_sprite_comp->get_num_verts());
    curr_sprite_comp->unbind();
  }
  LE_FATAL_ERROR_IF_GL_ERROR();
}

void graphics_system::p_render_tilemaps(
  space & target,
  mat3 const& world_to_NDC)
{
  LE::shader_program::use(*p_textured_shader_prog);

  GLint color_multiplier_ul = p_textured_shader_prog->get_unform_location("color_multiplier");
  GLint texture_ul = p_textured_shader_prog->get_unform_location("texture");
  GLint to_NDC_ul = p_textured_shader_prog->get_unform_location("to_NDC");

  texture::set_active_unit(0);
  glUniform1i(texture_ul, 0);

  glUniform4fv(color_multiplier_ul, 1, colors::white.data);

  for(auto tilemap_comp_it = target.engine_component_begin<tilemap_component>();
    tilemap_comp_it != target.engine_component_end<tilemap_component>();
    ++tilemap_comp_it)
  {
    tilemap_component const* curr_tilemap_comp
      = static_cast<tilemap_component const*>(*tilemap_comp_it);
    entity const* curr_ent = curr_tilemap_comp->get_owning_entity();
    auto const* curr_ent_t = curr_ent->get_component<transform_component>();

    mat3 const& model_to_world = curr_ent_t->get_matrix();
    mat3 const model_to_NDC = world_to_NDC * model_to_world;

    // Tileset data
    tileset const* curr_tileset = curr_tilemap_comp->get_tile_set();
    float tileset_tile_size = (float)curr_tileset->get_tile_size();

    // Tilemap data
    uvec2 num_tiles = curr_tilemap_comp->get_num_tiles();

    mat3 tile_to_model = identity_mat3;
    curr_tilemap_comp->bind();
    for(unsigned y = 0; y < num_tiles.y(); ++y)
    {
      for(unsigned x = 0; x < num_tiles.x(); ++x)
      {
        auto curr_tile_id = curr_tilemap_comp->get_tile_id(x, y);

        // Negative tile_id indicates no tile is to be drawn
        if(curr_tile_id < 0)
        {
          continue;
        }

        tile_to_model(0, 0) = tileset_tile_size;
        tile_to_model(1, 1) = tileset_tile_size;
        // Place tiles from top left of each tile.
        tile_to_model(0, 2) = (x * tileset_tile_size) + (tileset_tile_size * 0.5f);
        tile_to_model(1, 2) = (y * -tileset_tile_size) - (tileset_tile_size * 0.5f);
        mat3 tile_to_NDC = model_to_NDC * tile_to_model;
        glUniformMatrix3fv(to_NDC_ul, 1, GL_TRUE, tile_to_NDC.data);
        renderable_element_buffer::draw(
          GL_TRIANGLES,
          curr_tileset->get_tile_index_buffer_offset(curr_tile_id),
          tileset::num_indices_per_tile());
      }
    }
    curr_tilemap_comp->unbind();

  }
  LE_FATAL_ERROR_IF_GL_ERROR();
}

void graphics_system::p_render_ddraw(
  space & target,
  mat3 const& world_to_NDC)
{
  if(target.get_ddraw_enabled() == false)
  {
    return;
  }

  LE::shader_program::use(*p_debug_shader_prog);

  GLint to_NDC_ul = p_debug_shader_prog->get_unform_location("to_NDC");
  glUniformMatrix3fv(to_NDC_ul, 1, GL_TRUE, world_to_NDC.data);

  // TODO: Use camera mat
  target.m_world_ddraw.draw();
  target.m_world_ddraw.draw();

  // TODO: Use hud mat
  target.m_hud_ddraw.draw();

  LE_FATAL_ERROR_IF_GL_ERROR();
}

} // namespace LE
