#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "sys/time.h"
#include "omp.h"

void foo()
{
  printf("Running foo()... ");

  /* Begin of OpenMP setup */
  omp_set_default_device(0);
  /* End of OpenMP setup */

  const int x_m = 0;
  const int y_m = 0;
  const int z_m = 0;

  const int halox = 2;
  const int haloy = 2;
  const int haloz = 2;

  const int x_M = 511;
  const int y_M = 511;
  const int z_M = 511;

  const int nt = 2;
  const int nx = (x_M - x_m + 1) + halox;
  const int ny = (y_M - y_m + 1) + haloy;
  const int nz = (z_M - z_m + 1) + haloz;
  const size_t size = nt*nx*ny*nz;
  const size_t nbytes = size*sizeof(float);

  float * f0_vec;
  posix_memalign((void**)(&f0_vec), 64, nbytes);

  float (*restrict f0)[nx][ny][nz] = (float (*)[nx][ny][nz]) f0_vec;

  #pragma omp target enter data map(to: f0[0:nt][0:nx][0:ny][0:nz])

  for (int time = 0, t0 = (time)%(2), t1 = (time + 1)%(2); time <= 10; time += 1, t0 = (time)%(2), t1 = (time + 1)%(2))
  {
    #pragma omp target teams distribute parallel for collapse(3)
    for (int x = x_m; x <= x_M; x += 1)
    {
      for (int y = y_m; y <= y_M; y += 1)
      {
        for (int z = z_m; z <= z_M; z += 1)
        {
          f0[t1][x + 1][y + 1][z + 1] = f0[t0][x + 1][y + 1][z + 1] + 1.0F;
        }
      }
    }
  }

  #pragma omp target update from(f0[0:nt][0:nx][0:ny][0:nz])
  #pragma omp target exit data map(release: f0[0:nt][0:nx][0:ny][0:nz])

  free(f0_vec);

  printf("DONE!\n");
}
