#include <ruby.h>
#include <algorithm> // std::min
#include <fstream>
#include <arrayfire.h>
#include <stdio.h>
#include <math.h>
/*
 * Project Includes
 */

#include "arrayfire.h"
#include "ruby_arrayfire.h"

namespace arf {

  enum ewop_t {
    EW_ADD,
    EW_SUB,
    EW_MUL,
    EW_DIV,
    EW_POW,
    EW_MOD,
    EW_EQEQ,
    EW_NEQ,
    EW_LT,
    EW_GT,
    EW_LEQ,
    EW_GEQ,
  };

  // #include <cstdlib>
  using namespace af;
// create a small wrapper to benchmark
  static array A; // populated before each timing
  static void fn()
  {
      array B = matmul(A, A);  // matrix multiply
      B.eval();                // ensure evaluated
  }
  static void test()
  {
      double peak = 0;
      try {
          int device = 0;
          setDevice(device);
          info();
          printf("Benchmark N-by-N matrix multiply\n");
          for (int n = 128; n <= 2048; n += 128) {
              printf("%4d x %4d: ", n, n);
              A = constant(1,n,n);
              double time = timeit(fn); // time in seconds
              double gflops = 2.0 * powf(n,3) / (time * 1e9);
              if (gflops > peak)
                  peak = gflops;
              printf(" %4.0f Gflops\n", gflops);
              fflush(stdout);
          }
      } catch (af::exception& e) {
          fprintf(stderr, "%s\n", e.what());
          throw;
      }
      printf(" ### peak %g GFLOPS\n", peak);
  }

  static void createArray(afstruct *afarray)
  {
    dim_t dims[afarray->ndims] ;

    for (size_t index = 0; index < afarray->ndims; ++index){
      dims[index] = (dim_t)afarray->dimension[index];
    }

    af_create_array( &afarray->arr, afarray->array, afarray->ndims, dims, f64 );

    af_print_array(afarray->arr);
  }

  static void hostArray(afstruct *afarray)
  {

  }
}
extern "C" {
  #include "arrayfire.c"
}