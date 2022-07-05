#include "stdlib.h"
#include "omp.h"

int main(int argc, char* argv[])
{
  const int x_m = 0;
  const int x_M = 999;

  const int i0 = 1.0;
  const int i1 = 1.01;
  const int i2 = 1.02;
  const int i3 = 1.03;
  const int i4 = 1.04;
  const int i5 = 1.05;
  const int i6 = 1.06;
  const int i7 = 1.07;
  const int i8 = 1.08;
  const int i9 = 1.09;
  const int i10 = 1.10;
  const int i11 = 1.11;
  const int i12 = 1.12;
  const int i13 = 1.13;
  const int i14 = 1.14;
  const int i15 = 1.15;
  const int i16 = 1.16;
  const int i17 = 1.17;
  const int i18 = 1.18;
  const int i19 = 1.19;
  const int i20 = 1.20;
  const int i21 = 1.21;
  const int i22 = 1.22;
  const int i23 = 1.23;
  const int i24 = 1.24;
  const int i25 = 1.25;
  const int i26 = 1.26;
  const int i27 = 1.27;
  const int i28 = 1.28;
  const int i29 = 1.29;
  const int i30 = 1.30;

  const size_t size = 1000;

  float * f0;
  posix_memalign((void**)(&f0), 64, size*sizeof(float));

  #pragma omp target enter data map(to: f0[0:size])

  #pragma omp target teams distribute parallel for
  for (int x = x_m; x <= x_M; x += 1)
  {
    f0[x] = f0[x] + i0 + i1 + i2 + i3 + i4 + i5 + i6 + i7 + i8 + i9 + i10 + i11 + i12 + i13 + i14 + i15 + i16 + i17 + i18 + i19 + i20 + i21 + i22 + i23 + i24 + i25 + i26 + i27 + i28 + i29 + i30 +;
  }

  #pragma omp target update from(f0[0:size])
  #pragma omp target exit data map(release: f0[0:size])

  free(f0);

  return 0;
}
