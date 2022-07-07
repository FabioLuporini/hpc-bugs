#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

extern "C" void foo();

void foo() {
  MPI_Init(NULL, NULL);

  int world_rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
  int ngpus = omp_get_num_devices();
  omp_set_default_device((world_rank)%(ngpus));

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  if (world_size < 2) {
    fprintf(stderr, "World size must be greater than 1\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  const size_t nfloats = 1000*1000*1000;
  const size_t nbytes = nfloats*sizeof(float);
  float * f0 = (float *)omp_target_alloc(nbytes, omp_get_default_device());

  if (world_rank == 0) {
    MPI_Send(f0, nfloats, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
  } else if (world_rank == 1) {
    MPI_Recv(f0, nfloats, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  omp_target_free(f0, omp_get_default_device());


  MPI_Finalize();
}
