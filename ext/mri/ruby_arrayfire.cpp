#include <ruby.h>
#include <algorithm> // std::min
#include <fstream>

/*
 * Project Includes
 */

#include "arrayfire.h"
#include "ruby_arrayfire.h"

namespace arf {

}
extern "C" {
  #include "arrayfire.c"
}