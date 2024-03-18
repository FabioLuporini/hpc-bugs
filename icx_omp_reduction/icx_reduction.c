#define _POSIX_C_SOURCE 200809L

#include "stdlib.h"
#include "omp.h"

struct dataobj
{
  void *restrict data;
  unsigned long * size;
} ;

int Kernel(struct dataobj *restrict g_vec, struct dataobj *restrict h1_vec, const int t_M, const int t_m, const int x_M, const int x_m, const int y_m, const int nthreads)
{
  int (*restrict g)[g_vec->size[1]] __attribute__ ((aligned (64))) = (int (*)[g_vec->size[1]]) g_vec->data;
  float (*restrict h1)[h1_vec->size[1]] __attribute__ ((aligned (64))) = (float (*)[h1_vec->size[1]]) h1_vec->data;

  #pragma omp parallel num_threads(nthreads)
  {
    #pragma omp for collapse(2) schedule(static,1) reduction(+:h1[0][0])
    for (int t = t_m; t <= t_M; t += 1)
    {
      for (int x = x_m; x <= x_M; x += 1)
      {
        const int y_M = g[0][x];

        for (int y = y_m; y <= y_M; y += 1)
        {
          h1[0][0] += 1;
        }
      }
    }
  }

  return 0;
}
