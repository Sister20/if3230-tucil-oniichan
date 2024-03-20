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
  double matrix[mat_size][mat_size] = {
      {5, 1, 1},
      {1, 5, 1},
      {1, 1, 5}};

  // Getting the number elmt to receive
  int elmt_per_proc = mat_size / world_size;
  int remainder = mat_size % world_size;
  int recvcount = (proc_rank < remainder) ? (elmt_per_proc + 1) : elmt_per_proc;

  for (int i = 0; i < mat_size; i++)
  {
    // main loop for calculating the matrix inverse
    // Step 1: Divide the pivot row with the pivot elmt

    // Step 2: make the upper and lower row to be 0 other than the pivot elmt 
    
  }

  MPI_Finalize();
  return 0;
}