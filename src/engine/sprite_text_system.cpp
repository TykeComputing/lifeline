/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "sprite_text_system.h"

#include <common/fatal_construction_exception.h>
#include <common/fatal_error.h>
#include <common/logging.h>

namespace LE
{

sprite_text_system::sprite_text_system()
{
  SDL_version compiled;

  SDL_TTF_VERSION(&compiled);
  SDL_version const* linked = TTF_Linked_Version();

  log_status(log_scope::ENGINE, log_line_seperator);
  log_status(log_scope::ENGINE, "Compiled against SDL_ttf version {}.{}.{}...",
    (unsigned)compiled.major, (unsigned)compiled.minor, (unsigned)compiled.patch);
  log_status(log_scope::ENGINE, "Linked against SDL_ttf version {}.{}.{}...",
    (unsigned)linked->major, (unsigned)linked->minor, (unsigned)linked->patch);
  log_status(log_scope::ENGINE, log_line_seperator);

  if(TTF_Init() != 0)
  {
    LE_FATAL_ERROR(TTF_GetError());
    SDL_ClearError();
    throw fatal_construction_exception("Error initializing SDL, exiting...\n");
  }
}

sprite_text_system::~sprite_text_system()
{
  TTF_Quit();
}

} // namespace LE
