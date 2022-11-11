#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "sys/time.h"
#include "omp.h"

#define r0L0(x, y, z) r0[(x)*y_stride2 + (y)*z_stride2 + (z)]

void foo()
{
  printf("Running foo()...\n");
  fflush(stdout);

  omp_set_default_device(0);

  int x_size = 4;
  int y_size = 4;
  int z_size = 4;

  int x_m = 0;
  int y_m = 0;
  int z_m = 0;

  int x_M = 3;
  int y_M = 3;
  int z_M = 3;

  float * r0 = (float *)omp_target_alloc(y_size*z_size*x_size*sizeof(float),omp_get_default_device());

  const long y_fsz2 = y_size;
  const long z_fsz2 = z_size;

  const long y_stride2 = y_fsz2*z_fsz2;
  const long z_stride2 = z_fsz2;

  #pragma omp target teams distribute parallel for collapse(3) is_device_ptr(r0)
  for (int x = x_m; x <= x_M; x += 1)
  {
    for (int y = y_m; y <= y_M; y += 1)
    {
      for (int z = z_m; z <= z_M; z += 1)
      {
        r0L0(x, y, z) = 1.;
      }
    }
  }

  omp_target_free(r0, omp_get_default_device());

  printf("DONE!\n");
  fflush(stdout);

  return;
}
