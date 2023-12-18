#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "sys/time.h"
#include <sycl/sycl.hpp>

#define uL0(t,x,y) u[(t)*x_stride0 + (x)*y_stride0 + (y)]

using namespace sycl;

extern "C" void bar();

void bar()
{
  printf("Running bar()... \n");

  queue qid0(gpu_selector_v);

  const unsigned long nbytes = 500*500*500*4;

  float *vp = (float*) aligned_alloc(64, nbytes);
  float *d_vp = (float *)aligned_alloc_device(4096,nbytes,qid0);

  qid0.memcpy(d_vp,vp,nbytes);
  qid0.wait();

  free(vp);
  free(d_vp,qid0);
  qid0.wait();
}
