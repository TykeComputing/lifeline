/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "OS_interface.h"

#include <SDL2/SDL.h>

#include <common/logging.h>
#include <common/fatal_error.h>
#include <common/fatal_construction_exception.h>

namespace LE
{

OS_interface::OS_interface()
{
  int sdl_init_res = SDL_Init(SDL_INIT_VIDEO);
  if(sdl_init_res != 0)
  {
    LE_FATAL_ERROR(SDL_GetError());
    SDL_ClearError();
    throw fatal_construction_exception("Error initializing SDL, exiting...\n");
  }

  {
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    log_status(log_scope::ENGINE, "Compiled against SDL version {}.{}.{}...",
      (unsigned)compiled.major, (unsigned)compiled.minor, (unsigned)compiled.patch);
    log_status(log_scope::ENGINE, "Linked against SDL version {}.{}.{}...",
      (unsigned)linked.major, (unsigned)linked.minor, (unsigned)linked.patch);
  }
}

OS_interface::~OS_interface()
{
  SDL_Quit();
}

// TODO - Remove return value, have quit signaled via message once messaging system in place.
bool OS_interface::update()
{
  // TODO - Fully integrate here one game_hack is done (PollEvent loop is currently there to make hacking game input easier)
  //SDL_Event curr_event;
  //while(SDL_PollEvent(&curr_event))
  //{
  //  switch(curr_event.type)
  //  {
  //    case SDL_QUIT:
  //    {
  //      return false;
  //    }
  //    break;
  //  }
  //}

  //return true;
  return true;
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
