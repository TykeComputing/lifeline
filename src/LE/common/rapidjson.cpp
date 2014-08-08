/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "rapidjson.h"

#include <LE/common/file_string.h>
#include <LE/common/logging.h>

namespace LE
{
  bool parse_file(rapidjson::Document & doc, std::string const& file_name)
  {
    file_string file_data(file_name);
    if(file_data.is_valid() == false)
    {
      log_error(log_scope::ENGINE,
        "Unable to open json file \"{}\".", file_name);

      return false;
    }

    doc.Parse<0>(file_data.get_str().c_str());
    if(doc.HasParseError())
    {
      // rapidjson does not provide line/column, only character offset
      //   hacking it here until (if) rapidjson implements it
      std::string const& file_data_str = file_data.get_str();
      size_t const error_char_offset = doc.GetErrorOffset();
      std::string::const_iterator error_it =
        file_data_str.cbegin() + error_char_offset;

      // Compute line number, using 1 as base line
      size_t const error_line_num = 1 + std::count_if(
        file_data_str.cbegin(),
        error_it,
        std::bind2nd(std::equal_to<char>(), '\n'));

      // Compute column (char offset into line), using 1 as base column
      std::string::const_reverse_iterator reverse_error_it{error_it};
      auto error_line_begin_it = std::find(
        reverse_error_it,
        file_data_str.crend(),
        '\n');

        // If this is the first line we can
      size_t const error_column_num =
        error_line_begin_it != file_data_str.crend()
          ? std::distance(reverse_error_it, error_line_begin_it) + 1
          : error_char_offset + 1;

      // Log error
      log_error(log_scope::ENGINE, "Error parsing json file {}", file_name);
      log_error_no_prefix(log_line_seperator);
      log_error_no_prefix("== JSON ERRORS ==========");
      log_error_no_prefix("Line {}, Column {} - {}",
        error_line_num,
        error_column_num,
        doc.GetParseError());
      log_error_no_prefix(log_line_seperator);

      return false;
    }

    return true;
  }
}
