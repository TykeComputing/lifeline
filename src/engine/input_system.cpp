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

} // namespace LE
