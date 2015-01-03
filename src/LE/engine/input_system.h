/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_INPUT_SYSTEM_H
#define LE_ENGINE_INPUT_SYSTEM_H

#include <vector>

#include <SDL2/SDL.h>

#include <LE/math/vec.h>

namespace LE
{

enum mouse_button
{
  pc_mouse_button_left = SDL_BUTTON_LEFT,
  pc_mouse_button_middle = SDL_BUTTON_MIDDLE,
  pc_mouse_button_right = SDL_BUTTON_RIGHT
};

/*
 * WARNING: SDL must be initialized before using (anything more than construction).
 */
class input_system
{
public:
  input_system();

  void update_keystates();

  /*
   * Get if key is currently being held down.
   */
  bool is_key_pressed(SDL_Keycode key) const;

  /*
   * Get if key is was just pressed this frame.
   */
  bool is_key_triggered(SDL_Keycode key) const;

  /*
   * Get if key is was just un-pressed this frame.
   */
  bool is_key_released(SDL_Keycode key) const;

  bool is_mouse_pressed(mouse_button button) const;
  bool is_mouse_triggered(mouse_button button) const;
  bool is_mouse_released(mouse_button button) const;

  vec2 const& get_mouse_pos() const;
  vec2 const& get_prev_mouse_pos() const;
  vec2 get_delta_mouse_pos() const;

  void set_mouse_wheel_delta(vec2 const& new_delta);
  vec2 get_mouse_wheel_delta() const;

private:
  std::vector<bool> p_curr_states;
  std::vector<bool> p_prev_states;

  Uint32 p_curr_mouse_state;
  Uint32 p_prev_mouse_state;

  vec2 p_curr_mouse_pos;
  vec2 p_prev_mouse_pos;

  vec2 p_mouse_wheel_delta;
  bool p_mouse_wheel_set_this_update;

  bool p_ignore_keyboard;
  bool p_ignore_mouse;
};

} // namespace LE

#endif // LE_ENGINE_INPUT_SYSTEM_H
