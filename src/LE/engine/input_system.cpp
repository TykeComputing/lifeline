/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "input_system.h"

namespace LE
{

input_system::input_system() :
  p_curr_states(SDL_NUM_SCANCODES, false),
  p_prev_states(SDL_NUM_SCANCODES, false)
{

}

void input_system::update_keystates()
{
  // Keyboard
  int num_SDL_keys;
  Uint8 const* const SDL_key_states = SDL_GetKeyboardState(&num_SDL_keys);

  p_prev_states = p_curr_states;

  for(int i = 0; i < num_SDL_keys; ++i)
  {
    // SDL key state:
    //   0 - not pressed
    //   1 - pressed
    p_curr_states[i] = (SDL_key_states[i] == 1);
  }

  // Mouse
  p_prev_mouse_pos = p_curr_mouse_pos;
  p_prev_mouse_state = p_curr_mouse_state;

  int x, y;
  p_curr_mouse_state = SDL_GetMouseState(&x, &y);
  p_curr_mouse_pos.set((float)x, (float)y);

  // Quick hack
  if(p_mouse_wheel_set_this_update)
  {
    p_mouse_wheel_set_this_update = false;
  }
  else
  {
    p_mouse_wheel_delta = vec2::zero;
  }
}

bool input_system::is_key_pressed(SDL_Keycode key) const
{
  return p_curr_states[SDL_GetScancodeFromKey(key)];
}

bool input_system::is_key_triggered(SDL_Keycode key) const
{
  SDL_Scancode scan = SDL_GetScancodeFromKey(key);
  return (p_prev_states[scan] == false)
      && (p_curr_states[scan] == true);
}

bool input_system::is_key_released(SDL_Keycode key) const
{
  SDL_Scancode scan = SDL_GetScancodeFromKey(key);
  return (p_prev_states[scan] == true)
      && (p_curr_states[scan] == false);
}

bool input_system::is_mouse_pressed(mouse_button button) const
{
  return (p_curr_mouse_state & SDL_BUTTON(button))
      && (p_ignore_mouse == false);
}

bool input_system::is_mouse_triggered(mouse_button button) const
{
  return (p_curr_mouse_state & SDL_BUTTON(button))
      && (p_prev_mouse_state & SDL_BUTTON(button)) == SDL_RELEASED
      && (p_ignore_mouse == false);
}

bool input_system::is_mouse_released(mouse_button button) const
{
  return (p_curr_mouse_state & SDL_BUTTON(button)) == SDL_RELEASED
      && (p_prev_mouse_state & SDL_BUTTON(button))
      && (p_ignore_mouse == false);
}

vec2 const& input_system::get_mouse_pos() const
{
  return p_curr_mouse_pos;
}

vec2 const& input_system::get_prev_mouse_pos() const
{
  return p_prev_mouse_pos;
}

vec2 input_system::get_delta_mouse_pos() const
{
  return p_curr_mouse_pos - p_prev_mouse_pos;
}

void input_system::set_mouse_wheel_delta(vec2 const& new_delta)
{
  p_mouse_wheel_set_this_update = true;
  p_mouse_wheel_delta = new_delta;
}

vec2 input_system::get_mouse_wheel_delta() const
{
  return p_mouse_wheel_delta;
}

} // namespace LE
