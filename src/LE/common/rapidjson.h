/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_RAPIDJSON_H
#define LE_COMMON_RAPIDJSON_H

#include <string>

#include <rapidjson/document.h>

namespace LE
{
  bool parse_file(rapidjson::Document & doc, std::string const& file_name);
}

#endif // LE_COMMON_RAPIDJSON_H
