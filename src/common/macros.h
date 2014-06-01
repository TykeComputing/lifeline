/*
************************************************************************************************
Copyright 2014 Peter Clark

This file is part of Lifeline Engine.

Lifeline Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Lifeline Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Lifeline Engine.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************************
*/

#ifndef LE_COMMON_MACROS_H
#define LE_COMMON_MACROS_H

// Useful for unused function parameters, etc.
#define LE_UNUSED_VAR(x) (void)x

// N
#ifdef __GNUC__
#define LE_VAR_ATTR_UNUSED __attribute__((unused))
#else
#define LE_VAR_ATTR_UNUSED
#endif

// TODO - Consider using strongly typed enumerations(C++11)?
#define LE_ENUM_INTERNAL_1(a                                 ) enum value { e_start = 0, a = 0, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_2(a, b                              ) enum value { e_start = 0, a = 0, b, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_3(a, b, c                           ) enum value { e_start = 0, a = 0, b, c, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_4(a, b, c, d                        ) enum value { e_start = 0, a = 0, b, c, d, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_5(a, b, c, d, e                     ) enum value { e_start = 0, a = 0, b, c, d, e, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_6(a, b, c, d, e, f                  ) enum value { e_start = 0, a = 0, b, c, d, e, f, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_7(a, b, c, d, e, f, g               ) enum value { e_start = 0, a = 0, b, c, d, e, f, g, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_8(a, b, c, d, e, f, g, h            ) enum value { e_start = 0, a = 0, b, c, d, e, f, g, h, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_9(a, b, c, d, e, f, g, h, i         ) enum value { e_start = 0, a = 0, b, c, d, e, f, g, h, i, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_10(a, b, c, d, e, f, g, h, i, j      ) enum value { e_start = 0, a = 0, b, c, d, e, f, g, h, i, j, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_11(a, b, c, d, e, f, g, h, i, j, k   ) enum value { e_start = 0, a = 0, b, c, d, e, f, g, h, i, j, k, e_num_vals, e_end = e_num_vals - 1 };
#define LE_ENUM_INTERNAL_12(a, b, c, d, e, f, g, h, i, j, k, l) enum value { e_start = 0, a = 0, b, c, d, e, f, g, h, i, j, k, l, e_num_vals, e_end = e_num_vals - 1 };

#define LE_ENUM_STR_INTERNAL_1(a                                 ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a };
#define LE_ENUM_STR_INTERNAL_2(a, b                              ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b };
#define LE_ENUM_STR_INTERNAL_3(a, b, c                           ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c };
#define LE_ENUM_STR_INTERNAL_4(a, b, c, d                        ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c, #d };
#define LE_ENUM_STR_INTERNAL_5(a, b, c, d, e                     ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c, #d, #e };
#define LE_ENUM_STR_INTERNAL_6(a, b, c, d, e, f                  ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c, #d, #e, #f };
#define LE_ENUM_STR_INTERNAL_7(a, b, c, d, e, f, g               ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c, #d, #e, #f, #g };
#define LE_ENUM_STR_INTERNAL_8(a, b, c, d, e, f, g, h            ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c, #d, #e, #f, #g, #h };
#define LE_ENUM_STR_INTERNAL_9(a, b, c, d, e, f, g, h, i         ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c, #d, #e, #f, #g, #h, #i };
#define LE_ENUM_STR_INTERNAL_10(a, b, c, d, e, f, g, h, i, j      ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c, #d, #e, #f, #g, #h, #i, #j };
#define LE_ENUM_STR_INTERNAL_11(a, b, c, d, e, f, g, h, i, j, k   ) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c, #d, #e, #f, #g, #h, #i, #j, #k };
#define LE_ENUM_STR_INTERNAL_12(a, b, c, d, e, f, g, h, i, j, k, l) static const char * c_str[] LE_VAR_ATTR_UNUSED = { #a, #b, #c, #d, #e, #f, #g, #h, #i, #j, #k, #l };

#define LE_ENUM_1(enum_name, a                                 ) namespace enum_name { LE_ENUM_INTERNAL_1(a                                  )  LE_ENUM_STR_INTERNAL_1(a                                  ) }
#define LE_ENUM_2(enum_name, a, b                              ) namespace enum_name { LE_ENUM_INTERNAL_2(a, b                               )  LE_ENUM_STR_INTERNAL_2(a, b                               ) }
#define LE_ENUM_3(enum_name, a, b, c                           ) namespace enum_name { LE_ENUM_INTERNAL_3(a, b, c                            )  LE_ENUM_STR_INTERNAL_3(a, b, c                            ) }
#define LE_ENUM_4(enum_name, a, b, c, d                        ) namespace enum_name { LE_ENUM_INTERNAL_4(a, b, c, d                         )  LE_ENUM_STR_INTERNAL_4(a, b, c, d                         ) }
#define LE_ENUM_5(enum_name, a, b, c, d, e                     ) namespace enum_name { LE_ENUM_INTERNAL_5(a, b, c, d, e                      )  LE_ENUM_STR_INTERNAL_5(a, b, c, d, e                      ) }
#define LE_ENUM_6(enum_name, a, b, c, d, e, f                  ) namespace enum_name { LE_ENUM_INTERNAL_6(a, b, c, d, e, f                   )  LE_ENUM_STR_INTERNAL_6(a, b, c, d, e, f                   ) }
#define LE_ENUM_7(enum_name, a, b, c, d, e, f, g               ) namespace enum_name { LE_ENUM_INTERNAL_7(a, b, c, d, e, f, g                )  LE_ENUM_STR_INTERNAL_7(a, b, c, d, e, f, g                ) }
#define LE_ENUM_8(enum_name, a, b, c, d, e, f, g, h            ) namespace enum_name { LE_ENUM_INTERNAL_8(a, b, c, d, e, f, g, h             )  LE_ENUM_STR_INTERNAL_8(a, b, c, d, e, f, g, h             ) }
#define LE_ENUM_9(enum_name, a, b, c, d, e, f, g, h, i         ) namespace enum_name { LE_ENUM_INTERNAL_9(a, b, c, d, e, f, g, h, i          )  LE_ENUM_STR_INTERNAL_9(a, b, c, d, e, f, g, h, i          ) }
#define LE_ENUM_10(enum_name, a, b, c, d, e, f, g, h, i, j      ) namespace enum_name { LE_ENUM_INTERNAL_10(a, b, c, d, e, f, g, h, i, j      ) LE_ENUM_STR_INTERNAL_10(a, b, c, d, e, f, g, h, i, j      ) }
#define LE_ENUM_11(enum_name, a, b, c, d, e, f, g, h, i, j, k   ) namespace enum_name { LE_ENUM_INTERNAL_11(a, b, c, d, e, f, g, h, i, j, k   ) LE_ENUM_STR_INTERNAL_11(a, b, c, d, e, f, g, h, i, j, k   ) }
#define LE_ENUM_12(enum_name, a, b, c, d, e, f, g, h, i, j, k, l) namespace enum_name { LE_ENUM_INTERNAL_12(a, b, c, d, e, f, g, h, i, j, k, l) LE_ENUM_STR_INTERNAL_12(a, b, c, d, e, f, g, h, i, j, k, l) }

#endif // LE_COMMON_MACROS_H
