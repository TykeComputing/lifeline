/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_DEBUG_SHAPE_DRAWER_H
#define LE_GRAPHICS_DEBUG_SHAPE_DRAWER_H

#include <vector>

#include <common/macros.h>

#include <math/mat.h>
#include <math/vec.h>

#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>
#include <graphics/vertex.h>

namespace LE
{

/*
 * Base class for debug drawers.
 *
 * NOTE - Debug drawers must be manually cleared once per draw.
 */
class debug_drawer_base
{
public:
  LE_NON_COPYABLE(debug_drawer_base)

  bool empty() const;

  void clear();

  void reserve(size_t amount);

protected:
  debug_drawer_base();
  virtual ~debug_drawer_base();

  std::vector<debug_shape_vertex> p_vertices;

  void draw(GLenum prim_mode) const;

private:
  vertex_array p_VAO;
  vertex_buffer p_VBO;

  void _aquire_buffer();
  void _release_buffer();
};

class debug_line_drawer : public debug_drawer_base
{
public:
  struct settings
  {
    float arrow_head_size_percent = 0.1f;
    float max_arrow_head_size = 64.0f;
    unsigned circle_num_lines = 36;
  };

  void draw() const;

  void add_line(vec2 const& p0, vec2 const& p1, vec4 const& color);

  void add_circle(vec2 const& p, float r, vec4 const& color);

  void add_arrow(vec2 const& p0, vec2 const& norm_dir, float length, vec4 const& color);
  void add_arrow(vec2 const& p0, vec2 const& v, vec4 const& color);

  void add_aabb(vec2 const& min, vec2 const& max, vec4 const& color);

  void add_transform(mat3 const& transform, float scale);

  void reserve_lines(size_t amount);

  settings m_settings;
};

class debug_point_drawer : public debug_drawer_base
{
public:
  void draw() const;

  void add_point(vec2 const& p0, vec4 const& color);
};

} // namespace LE

#endif // LE_GRAPHICS_DEBUG_SHAPE_DRAWER_H
