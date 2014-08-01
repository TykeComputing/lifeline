/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "TTF_system.h"

#include <algorithm>
#include <vector>

#include <LE/common/fatal_construction_exception.h>
#include <LE/common/fatal_error.h>
#include <LE/common/logging.h>
#include <LE/common/resource_exception.h>
#include <LE/common/resource_manager.h>

namespace LE
{

class true_type_font
{
public:
  true_type_font(std::string const& file_path, unsigned size)
  {
    p_raw_font = TTF_OpenFont(file_path.c_str(), static_cast<int>(size));
    if(p_raw_font == nullptr)
    {
      resource_exception except(TTF_GetError());
      SDL_ClearError();
      throw except;
    }
  }

  ~true_type_font()
  {
    TTF_CloseFont(p_raw_font);
  }

  TTF_Font * get_raw() { return p_raw_font; }
  TTF_Font const* get_raw() const { return p_raw_font; }

private:
  TTF_Font * p_raw_font = nullptr;
};

TTF_system::TTF_system()
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
    LE_FATAL_ERROR("{}", TTF_GetError());
    SDL_ClearError();
    throw fatal_construction_exception("Error initializing SDL, exiting...\n");
  }
}

TTF_system::~TTF_system()
{
  TTF_Quit();
}

texture2D * TTF_system::render_text_to_texture(std::string const& text, unsigned size)
{
  static std::string const font_file_path =
    resource_manager::get_resource_dir() + "fonts/rambla/Rambla-Regular.ttf";

  // TODO: Store font instead of creating each time
  true_type_font rambla_ttf(font_file_path, size);

  // Quick hack to allow rendering of multiple lines using newlines.
  Uint32 wrap_length = 0;
  if(text.empty() == false)
  {
    // Finds what the rendered text width will be, since the only way to get SDL_ttf to handle
    //   newlines is by using TTF_RenderText_Blended_Wrapped, which requires a wrap_length.
    //   STL_ttf will pad the texture to this size, so I need to find the actual size (vs
    //   using very large value).
    // Slow and dirty, just needs to get job done for now.
    std::vector<std::string> lines;
    size_t line_start = 0;
    size_t newline_pos = text.find('\n');
    while(newline_pos != std::string::npos)
    {
      lines.push_back(text.substr(line_start, newline_pos - line_start));

      line_start = newline_pos + 1;
      newline_pos = text.find('\n', line_start);
    }

    // Get last line if it did not end with a newline
    if(text.back() != '\n')
    {
      lines.push_back(text.substr(line_start, text.length() - line_start));
    }

    auto longest_line_it = std::max_element(lines.begin(), lines.end(),
      [](std::string const& lhs, std::string const& rhs)->bool
      {
        return lhs.length() < rhs.length();
      });

    int w, h;
    TTF_SizeText(rambla_ttf.get_raw(), longest_line_it->c_str(), &w, &h);

    wrap_length = w;
  }

  SDL_Surface * text_surface = TTF_RenderText_Blended_Wrapped(
    rambla_ttf.get_raw(),
    text.c_str(),
    SDL_Color{255, 255, 255, 255}, wrap_length);
  if(text_surface == nullptr)
  {
    LE_FATAL_ERROR("{}", TTF_GetError());
    resource_exception except(TTF_GetError());
    SDL_ClearError();
    throw except;
  }

  texture2D * text_texture = new texture2D;
  text_texture->set_data(
    GL_RGBA8,
    text_surface->w,
    text_surface->h,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    text_surface->pixels);
  SDL_FreeSurface(text_surface);

  return text_texture;
}

} // namespace LE
