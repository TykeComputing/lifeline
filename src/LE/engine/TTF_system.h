/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_TTF_SYSTEM_H
#define LE_ENGINE_TTF_SYSTEM_H

#include <SDL2/SDL_ttf.h>

#include <LE/graphics/texture.h>

namespace LE
{

// Temporary hack for font creation
class TTF_system
{
public:
  TTF_system();
  ~TTF_system();

  // NOTE: TTF system must created before calling.
  static texture2D * render_text_to_texture(std::string const& text, unsigned size);

private:
};

} // namespace LE

#endif // LE_ENGINE_SPRITE_TEXT_SYSTEM_H
