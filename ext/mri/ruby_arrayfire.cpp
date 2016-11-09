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

  static void createArray(VALUE args, afstruct *afarray)
  {
    af_array arr;

    double data[4] = {1000.0, 2.0, 3.4, 7.0};
    const dim_t dims[2] = {2,2};
    af_array a2;
    af_create_array( &afarray->arr, &args, 2, dims,f64 );
    af_create_array( &arr, data, 2, dims,f64 );
    af_create_array( &a2, data, 2, dims,f64 );
    // array A(100, f64);
    af_array out;

    af_add( &out, arr, a2, 0);
    af_print_array(out);

  }
}
extern "C" {
  #include "arrayfire.c"
}