#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "sys/time.h"
#include <sycl/sycl.hpp>

#define uL0(t,x,y) u[(t)*x_stride0 + (x)*y_stride0 + (y)]

using namespace sycl;

extern "C" void foo1();

void foo1()
{
  printf("Running foo1()... \n");

  queue qid0(cpu_selector_v);

  const int x_m = 0;
  const int y_m = 0;

  const int halox = 2;
  const int haloy = 2;

  const int x_M = 7;
  const int y_M = 7;

  const int nt = 2;
  const int nx = (x_M - x_m + 1) + halox;
  const int ny = (y_M - y_m + 1) + haloy;
  const size_t size = nt*nx*ny;
  const size_t nbytes = size*sizeof(int);

  int * u;
  posix_memalign((void**)(&u), 64, nbytes);

  const long x_fsz0 = nx;
  const long y_fsz0 = ny;

  const long x_stride0 = x_fsz0*y_fsz0;
  const long y_stride0 = y_fsz0;

  range<2> kr0(x_M - x_m + 1,y_M - y_m + 1);
  qid0.submit([&](handler& h)
  {
    h.parallel_for(kr0,[=](id<2> idx)
    {
      int x = x_m + (int)(idx[0]);
      int y = y_m + (int)(idx[1]);

      uL0(1, x + 1, y + 1) = 2;
      uL0(0, x + 1, y + 1) = uL0(1, x + 1, y + 1) + 1;
    });
  });
  qid0.wait();

  for (int x = x_m; x <= x_M; x++)
  {
    for (int y = y_m; y <= y_M; y++)
    {
      printf("%d ", uL0(0, x + 1, y + 1));
    }
    printf("\n");
  }
  printf("\n");

  free(u);

  printf("DONE!\n");
}
