#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char **argv)
{
  // Init mpi
  MPI_Init(&argc, &argv);

  // Getting the rank and world size
  int proc_rank;
  int world_size;

  // Setup the root proc
  int root = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Getting the matrix
  int mat_size = 3;
  double matrix[mat_size][2 * mat_size] = {
      {5, 1, 1, 1, 0, 0},
      {1, 5, 1, 0, 1, 0},
      {1, 1, 5, 0, 0, 1}
  };

  // Getting the number elmt to receive
  int elmt_per_proc = (2 * mat_size) / world_size;
  int remainder = (2 * mat_size) % world_size;
  int recvcount = (proc_rank < remainder) ? (elmt_per_proc + 1) : elmt_per_proc;

  for (int i = 0; i < mat_size; i++)
  {
    // main loop for calculating the matrix inverse
    // Step 1: Divide the pivot row with the pivot elmt
    double *numerator = (double *) malloc(sizeof(MPI_DOUBLE) * recvcount);
    MPI_Scatter(
      matrix[i],
      recvcount,
      MPI_DOUBLE,
      numerator,
      recvcount,
      MPI_DOUBLE,
      root,
      MPI_COMM_WORLD
    );

    double denominator;
    if (proc_rank == root) {
      denominator = matrix[i][i];
    }
    MPI_Bcast(
      &denominator,
      1,
      MPI_DOUBLE,
      root,
      MPI_COMM_WORLD
    );

    for (int j = 0; j < recvcount; j++) {
      // printf("num: %.17f\n", numerator[j]);
      // printf("den: %.17f\n", denominator);
      numerator[j] = numerator[j] / denominator;
    }

    double *pivot_row = NULL;
    if (proc_rank == root) {
      pivot_row = (double *) malloc(sizeof(double) * 2 * mat_size);
    }

    MPI_Gather(
      numerator,
      recvcount,
      MPI_DOUBLE,
      pivot_row,
      recvcount,
      MPI_DOUBLE,
      root,
      MPI_COMM_WORLD
    );

    if (proc_rank == root) {
      for (int j = 0; j < 2 * mat_size; j++) {
        printf("%.17f ", pivot_row[j]);
      }
      printf("\n");
    }

    // Step 2: make the upper and lower row to be 0 other than the pivot elmt 
    
  }

  MPI_Finalize();
  return 0;
}