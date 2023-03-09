#define _POSIX_C_SOURCE 200809L
#define START_TIMER(S) struct timeval start_ ## S , end_ ## S ; gettimeofday(&start_ ## S , NULL);
#define STOP_TIMER(S,T) gettimeofday(&end_ ## S, NULL); T->S += (double)(end_ ## S .tv_sec-start_ ## S.tv_sec)+(double)(end_ ## S .tv_usec-start_ ## S .tv_usec)/1000000;

#include "stdlib.h"
#include "math.h"
#include "sys/time.h"
#include "xmmintrin.h"
#include "pmmintrin.h"
#include "omp.h"

struct dataobj
{
  void *restrict data;
  unsigned long * size;
  unsigned long * npsize;
  unsigned long * dsize;
  int * hsize;
  int * hofs;
  int * oofs;
  void * dmap;
} ;

struct profiler
{
  double section0;
} ;


int Kernel(struct dataobj *restrict g_vec, struct dataobj *restrict h1_vec, const int t_M, const int t_m, const int x_M, const int x_m, const int y_m, const int nthreads, struct profiler * timers)
{
  int (*restrict g)[g_vec->size[1]] __attribute__ ((aligned (64))) = (int (*)[g_vec->size[1]]) g_vec->data;
  float (*restrict h1)[h1_vec->size[1]] __attribute__ ((aligned (64))) = (float (*)[h1_vec->size[1]]) h1_vec->data;

  /* Begin section0 */
  START_TIMER(section0)
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
  STOP_TIMER(section0,timers)
  /* End section0 */

  return 0;
}
/* Backdoor edit at Thu Mar  9 23:22:27 2023*/ 
/* Backdoor edit at Thu Mar  9 23:23:01 2023*/ 
