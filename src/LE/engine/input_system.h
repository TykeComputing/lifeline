/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_INPUT_SYSTEM_H
#define LE_ENGINE_INPUT_SYSTEM_H

#include <vector>

#include <SDL2/SDL.h>

namespace LE
{

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

private:
  std::vector<bool> p_curr_states;
  std::vector<bool> p_prev_states;
};

} // namespace LE

#endif // LE_ENGINE_INPUT_SYSTEM_H
