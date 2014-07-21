/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "OS_interface.h"

#include <SDL2/SDL.h>

#include <LE/common/logging.h>
#include <LE/common/fatal_error.h>
#include <LE/common/fatal_construction_exception.h>

// TODO - Remove if messaging is implemented
#include <LE/engine/engine.h>

namespace LE
{

OS_interface::OS_interface()
{
  SDL_version compiled;
  SDL_version linked;

  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);

  log_status(log_scope::ENGINE, log_line_seperator);
  log_status(log_scope::ENGINE, "Compiled against SDL version {}.{}.{}...",
    (unsigned)compiled.major, (unsigned)compiled.minor, (unsigned)compiled.patch);
  log_status(log_scope::ENGINE, "Linked against SDL version {}.{}.{}...",
    (unsigned)linked.major, (unsigned)linked.minor, (unsigned)linked.patch);
  log_status(log_scope::ENGINE, log_line_seperator);

  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    LE_FATAL_ERROR(SDL_GetError());
    SDL_ClearError();
    throw fatal_construction_exception("Error initializing SDL, exiting...\n");
  }
}

OS_interface::~OS_interface()
{
  SDL_Quit();
}

// TODO - Remove return value, have quit signaled via message once messaging system in place.
void OS_interface::update(engine & game_engine, input_system & input_sys)
{
  SDL_Event curr_event;
  while(SDL_PollEvent(&curr_event))
  {
    switch(curr_event.type)
    {
      case SDL_QUIT:
      {
        game_engine.set_is_running(false);
      }
      break;
    }
  }

  // Quick super easy hack
  // NOTE: Must be called after all SDL_PollEvents
  // TODO - Consider updating based on SDL_Events?
  input_sys.update_keystates();
}

std::string OS_interface::get_base_dir() const
{
  char * cwd_c_str = SDL_GetBasePath();
  if(cwd_c_str)
  {
    std::string cwd(cwd_c_str);
    SDL_free(cwd_c_str);
    return cwd;
  }
  else
  {
    LE_FATAL_ERROR(SDL_GetError());
    SDL_ClearError();
    return std::string("Unable to get working directory.");
  }
}

std::string OS_interface::get_preferred_dir() const
{
//  char * cwd_c_str = SDL_GetPrefPath();
//  if(cwd_c_str)
//  {
//    std::string cwd(cwd_c_str);
//    SDL_free(cwd_c_str);
//    return cwd;
//  }
//  else
//  {
//    LE_FATAL_ERROR(SDL_GetError());
//    SDL_ClearError();
//    return std::string("Unable to get working directory.");
//  }
  return {};
}

} // namespace LE
