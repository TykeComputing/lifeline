#include <algorithm> // transform
#include <cctype>    // toupper
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

typedef std::vector< std::pair<std::string, std::string> > token_container;

void print_error_and_exit(std::string error_msg)
{
  std::cerr << error_msg << ", exiting..." << std::endl;
  std::exit(-1);
}

void read_tokens_from_config_file(token_container & tokens)
{
  std::string config_file_name("cppclassgen.cfg");
  std::ifstream config_file(config_file_name);
  if(!config_file.is_open())
  {
    print_error_and_exit("Error opening config file \"" + config_file_name + "\"");
  }

  std::string curr_line;
  while(std::getline(config_file, curr_line))
  {
    std::stringstream curr_line_stream(curr_line);
    std::string curr_token, curr_replacement_value;
    curr_line_stream >> curr_token;
    curr_line_stream >> curr_replacement_value;

    // Ignore lines with < 2 entires (ex. final empty line)
    if(!curr_token.empty() && !curr_replacement_value.empty())
    {
      tokens.push_back(std::make_pair(curr_token, curr_replacement_value));
    }
  }
}

void create_new_file_from_template(
    token_container const& tokens,
    std::string const& class_name,
    std::string const& file_extension)
{
  std::string template_file_name = "template" + file_extension;
  std::ifstream template_file(template_file_name);
  if(!template_file.is_open())
  {
    print_error_and_exit("Error opening template file \"" + template_file_name + "\"");
  }

  // Read file into string
  std::string file_string(
    (std::istreambuf_iterator<char>(template_file)),
     std::istreambuf_iterator<char>());

  // Search for each token through the entire file, replacing as found.
  for(auto token_value_pair : tokens)
  {
    size_t remove_it = file_string.find(token_value_pair.first);
    while(remove_it != std::string::npos)
    {
      // Find end of token (we searched for the whole token including %'s thus it is guaranteed
      //   that it exists)
      size_t remove_end_it = file_string.find('%', remove_it + 1);
      size_t token_length = (remove_end_it + 1) - remove_it;

      // Replace entire token from remove_it to and including remove_end.
      file_string.replace(remove_it, token_length, token_value_pair.second);

      remove_it = file_string.find(token_value_pair.first.c_str(), remove_it);
    }
  }

  std::string output_file_name = class_name + file_extension;
  std::ofstream output_file(output_file_name);
  if(!output_file.is_open())
  {
    std::cerr << "Error opening ouput file \"" << output_file_name << "\"exiting..." << std::endl;
    std::exit(-1);
  }

  output_file << file_string;

  std::cout << output_file_name << " written..." << std::endl;
}

void toupper(std::string & s)
{
  std::transform(s.begin(), s.end(),
                 s.begin(),
                 [](char c) ->char { return static_cast<char>(std::toupper(c)); });
}

int main(int arg_count, char *args[])
{
  if(arg_count != 2 && arg_count != 3)
  {
    std::cerr << "Usage: cppclassgen <class_name> <module_name(optional)>" << std::endl;
    std::exit(-1);
  }

  token_container tokens;

  std::string class_name(args[1]);
  tokens.push_back(std::make_pair("%CLASS_NAME%", class_name));
  toupper(class_name);
  tokens.push_back(std::make_pair("%CLASS_NAME_UPPER%", class_name));

  if(arg_count == 3)
  {
    std::string module_name(args[2]);
    tokens.push_back(std::make_pair("%MODULE_NAME%", module_name));
    toupper(module_name);
    tokens.push_back(std::make_pair("%MODULE_NAME_UPPER%", module_name));
  }

  read_tokens_from_config_file(tokens);
  create_new_file_from_template(tokens, args[1], ".h");
  create_new_file_from_template(tokens, args[1], ".cpp");

  return 0;
}
