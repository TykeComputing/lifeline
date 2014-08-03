/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_GRAPHICS_SYSTEM_H
#define LE_ENGINE_GRAPHICS_SYSTEM_H

#include <LE/engine/space.h>

#include <LE/graphics/shader_program.h>

#include <LE/math/vec.h>

namespace LE
{

class graphics_system
{
public:
  graphics_system();

  void clear_render_target();
  void render(space & target);

  /*
   * Calculates a new render target size based on window_size that will keep 1 pixel in the
   *   render target scalable to one pixel in the window.
   */
  void update_render_target_size(uvec2 const& window_size);
  uvec2 const& get_render_target_size() const;

private:
  void p_load_shader(
    std::unique_ptr<shader_program> & out_sp,
    char const* vert,
    char const* frag);

  void p_render_sprites(
    space & target,
    mat3 const& world_to_NDC);
  void p_render_tilemaps(
    space & target,
    mat3 const& world_to_NDC);

  std::unique_ptr<shader_program> p_textured_shader_prog;
  std::unique_ptr<shader_program> p_debug_shader_prog;

  uvec2 p_render_target_size = uvec2::zero;
};

} // namespace LE

#endif // LE_ENGINE_GRAPHICS_SYSTEM_H
