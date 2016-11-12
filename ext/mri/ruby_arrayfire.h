#ifndef RUBY_ARRAYFIRE_H
  #define RUBY_ARRAYFIRE_H
#endif


typedef struct AF_STRUCT
{
  af_array arr;
  int ndims;
  size_t dimension;     // Method of storage (csc, dense, etc).
  size_t array;
}afstruct;

/*
 * Functions
 */

#ifdef __cplusplus
typedef VALUE (*METHOD)(...);
//}; // end of namespace nm
#endif

#include <ruby.h>
// #include <test.cpp>
#ifdef __cplusplus
extern "C" {
#endif

  void Init_arrayfire();
  static void test();
  // External API
  static void createArray(VALUE args, afstruct *afarray);

#ifdef __cplusplus
}
#endif
