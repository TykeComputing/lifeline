/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

namespace LE
{

template<typename SCOPE_T>
unique_id<SCOPE_T>::unique_id() :
  p_value(get_next())
{
}

template<typename SCOPE_T>
typename unique_id<SCOPE_T>::value_type unique_id<SCOPE_T>::get_next()
{
  static value_type curr_id = 0;
  return curr_id++;
}

} // namespace LE
