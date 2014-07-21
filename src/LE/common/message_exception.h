/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_MESSAGE_EXCEPTION_H
#define LE_COMMON_MESSAGE_EXCEPTION_H

#include <string>
#include <iosfwd>

namespace LE
{

// TODO - Look at avoiding needless copies of exceptions when thrown
class message_exception
{
public:
  message_exception();
  virtual ~message_exception() {}
  message_exception(char const* message);
  message_exception(std::string const& message);

  std::string const& what() const;

private:
  std::string p_message;
};

} // namespace LE

#endif // LE_COMMON_MESSAGE_EXCEPTION_H
