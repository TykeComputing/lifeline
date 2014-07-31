#include <algorithm> // transform
#include <cctype>    // toupper
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

struct generator
{
  typedef std::vector< std::pair<std::string, std::string> > token_container;

  token_container m_tokens;
  std::string m_template_file = "generic";
};

void print_error_and_exit(std::string error_msg)
{
  std::cerr << error_msg << ", exiting..." << std::endl;
  std::exit(-1);
}

typedef void(*process_option_func)(generator & gen, std::string const& val);

void process_set_template_file(generator & gen, std::string const& val)
{
  gen.m_template_file = val;
}

int process_options(generator & gen, int arg_count, char *args[])
{
  std::unordered_map<std::string, process_option_func> options(
  {
    { "template", process_set_template_file }
  });

  for(int arg_it = 1; arg_it < arg_count; ++arg_it)
  {
    std::string curr_arg(args[arg_it]);

    // All options begin with `--`
    if(curr_arg.find("--") != 0)
    {
      // Return index of first non-flag
      return arg_it;
    }
    else
    {
      curr_arg.erase(0, 2);
    }

    // Transform input from `--<arg_name>=<value>` to `--<arg_name>` and `<value>`
    auto arg_value_separator_pos = curr_arg.find('=');
    if(arg_value_separator_pos == std::string::npos
    || arg_value_separator_pos >= curr_arg.size())
    {
      std::cerr << "Malformed option specified: \"" << curr_arg << "\"" << std::endl;
      continue;
    }

    std::string curr_val(curr_arg, arg_value_separator_pos + 1);
    curr_arg.erase(arg_value_separator_pos);

    // Call appropriate handler if one exists
    auto handler_find_it = options.find(curr_arg);
    if(handler_find_it != options.end())
    {
      handler_find_it->second(gen, curr_val);
    }
    else
    {
      std::cerr << "Invalid option specified: \"" << curr_arg << "\"" << std::endl;
    }
  }

  return arg_count;
}

void read_tokens_from_config_file(generator & gen)
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
      gen.m_tokens.push_back(std::make_pair(curr_token, curr_replacement_value));
    }
  }
}

void create_new_file_from_template(
    generator const& gen,
    std::string const& class_name,
    std::string const& file_extension)
{
  std::string template_file_name = gen.m_template_file + file_extension + ".template";
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
  for(auto token_value_pair : gen.m_tokens)
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

std::string toupper(std::string const& s)
{
  std::string upper;
  upper.reserve(s.size());
  std::transform(s.begin(), s.end(),
                 std::back_inserter(upper),
                 [](char c) ->char { return std::toupper(c); });
  return upper;
}

int main(int arg_count, char *args[])
{
  generator gen;
  int first_non_flag_index = process_options(gen, arg_count, args);
  int num_non_flag_args = arg_count - first_non_flag_index;

  if(num_non_flag_args != 1 && num_non_flag_args != 2)
  {
    std::cerr << "Usage: cppclassgen --<flags> <class_name> <module_name(optional)>" << std::endl;
    std::exit(-1);
  }

  std::string class_name(args[first_non_flag_index]);
  gen.m_tokens.push_back(std::make_pair("%CLASS_NAME%", class_name));
  auto class_name_upper = toupper(class_name);
  gen.m_tokens.push_back(std::make_pair("%CLASS_NAME_UPPER%", class_name_upper));

  if(num_non_flag_args == 2)
  {
    std::string module_name(args[first_non_flag_index + 1]);
    gen.m_tokens.push_back(std::make_pair("%MODULE_NAME%", module_name));
    toupper(module_name);
    auto module_name_upper = toupper(module_name);
    gen.m_tokens.push_back(std::make_pair("%MODULE_NAME_UPPER%", module_name_upper));
  }

  read_tokens_from_config_file(gen);
  create_new_file_from_template(gen, class_name, ".h");
  create_new_file_from_template(gen, class_name, ".cpp");

  return 0;
}
