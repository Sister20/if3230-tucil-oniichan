#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void readfile(double ***mat, int *size)
{
  cin >> *size;

  *mat = new double *[*size];
  for (int i = 0; i < *size; i++)
  {
    (*mat)[i] = new double[2 * (*size)]();
  }

  for (int i = 0; i < *size; i++)
  {
    for (int j = 0; j < *size; j++)
    {
      cin >> (*mat)[i][j];
    }
  }

  for (int i = 0; i < *size; i++)
  {
    for (int j = *size; j < (*size) * 2; j++)
    {
      if (i + *size == j)
      {
        (*mat)[i][j] = 1;
      }
      else
      {
        (*mat)[i][j] = 0;
      }
    }
  }
}

void clear(double **mat)
{
  free(mat);
}

// Display a 2d matrix
void printMatrix(double *matrix, int count_width, int count_row)
{
  for (int i = 0; i < count_row; i++)
  {
    for (int j = 0; j < count_width; j++)
    {
      cout << *(matrix + j + i * 6) << " ";
      if (j == (count_width / 2)-1) {
        cout << "|";
      }
    }
    cout << endl;
  }
}

void setupRecvCountStep1(int *elmt_per_proc_step1, int ideal_elmt_per_proc_step1, int remainder_elmt_per_proc_step1, int world_size)
{
  for (int i = 0; i < world_size; i++)
  {
    if (i < remainder_elmt_per_proc_step1)
    {
      elmt_per_proc_step1[i] = ideal_elmt_per_proc_step1 + 1;
    }
    else
    {
      elmt_per_proc_step1[i] = ideal_elmt_per_proc_step1;
    }
  }
}

void setupRecvCountStep2(int *array_per_proc, int *elmt_per_proc, int world_size, int mat_size, int remainder, int ideal_array_per_proc)
{
  for (int i = 0; i < world_size; i++)
  {
    if (i < remainder)
    {
      array_per_proc[i] = ideal_array_per_proc + 1;
    }
    else
    {
      array_per_proc[i] = ideal_array_per_proc;
    }
    elmt_per_proc[i] = array_per_proc[i] * mat_size * 2;
  }
}

void setupOffsetStep1(int *elmt_offset, int elmt_per_proc[], int world_size)
{
  for (int i = 0; i < world_size; i++)
  {
    if (i == 0)
    {
      elmt_offset[i] = 0;
    }
    else
    {
      elmt_offset[i] = elmt_offset[i - 1] + elmt_per_proc[i - 1];
    }
  }
}

void setupOffsetStep2(int *array_offset, int *elmt_offset, int array_per_proc[], int world_size, int mat_size)
{
  for (int i = 0; i < world_size; i++)
  {
    if (i == 0)
    {
      array_offset[i] = 0;
    }
    else
    {
      array_offset[i] = array_offset[i - 1] + array_per_proc[i - 1];
    }
    elmt_offset[i] = array_offset[i] * mat_size * 2;
  }
}

int main(int argc, char **argv)
{
  // Init mpi
  MPI_Init(&argc, &argv);

  // Getting the rank and world size
  int proc_rank;
  int world_size;

  MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Setup the root proc
  int rootproc = 0;

  // Getting the matrix size
  int mat_size = 3;
  int count_x = mat_size;
  int count_y = mat_size * 2;

  // init matrix as pointer
  double *matrix;

  if (proc_rank == rootproc)
  {
    // getting the matrix
    // TODO: Change it using the parser lib when done
    matrix = (double *)malloc(count_x * count_y * sizeof(double));
    double test_matrix[mat_size][6] = {{5, 1, 1, 1, 0, 0},
                                       {1, 5, 1, 0, 1, 0},
                                       {1, 1, 5, 0, 0, 1}};
    memcpy(matrix, test_matrix, count_x * count_y * sizeof(double));
  }

  // Getting the number elmt to send and receive
  int ideal_array_per_proc_step1 = count_y / world_size;
  int remainder_step1 = count_y % world_size;

  int ideal_array_per_proc = mat_size / world_size;
  int remainder = mat_size % world_size;

  int elmt_per_proc_step1[world_size] = {0};
  setupRecvCountStep1(elmt_per_proc_step1, ideal_array_per_proc_step1, remainder_step1, world_size);
  int array_per_proc[world_size] = {0};
  int elmt_per_proc[world_size] = {0};
  setupRecvCountStep2(array_per_proc, elmt_per_proc, world_size, mat_size, remainder, ideal_array_per_proc);

  // setup the offset
  int elmt_offset_step1[world_size] = {0};
  setupOffsetStep1(elmt_offset_step1, elmt_per_proc_step1, world_size);
  int array_offset[world_size] = {0};
  int elmt_offset[world_size] = {0};
  setupOffsetStep2(array_offset, elmt_offset, array_per_proc, world_size, mat_size);

  // Init Receive Buffer (this part is independent from each process)
  double bcastbuff_step1 = {0};
  double *recvbuff_step1 = (double *)malloc(elmt_per_proc_step1[proc_rank] * sizeof(double));

  // Receive buffer for the second step
  double bcastbuff_step2[count_y] = {0};
  double *recvbuff_step2 = (double *)malloc(array_per_proc[proc_rank] * count_y * sizeof(double));

  for (int pivot = 0; pivot < mat_size; pivot++)
  {
    // Step 1 - Divide the all row with the pivot elmt
    if (proc_rank == rootproc)
    {
      // init bcast buffer
      bcastbuff_step1 = *(matrix + (pivot * count_y + pivot));
      // DEBUG purposes only
      // cout << "matrix 0" << endl;
      // printMatrix(matrix, 6, 3);
    }
    MPI_Bcast(&bcastbuff_step1, 1, MPI_DOUBLE, rootproc, MPI_COMM_WORLD);
    MPI_Scatterv(matrix + pivot * count_y, elmt_per_proc_step1, elmt_offset_step1, MPI_DOUBLE, recvbuff_step1, elmt_per_proc_step1[proc_rank], MPI_DOUBLE, rootproc, MPI_COMM_WORLD);

    for (int i = 0; i < elmt_per_proc_step1[proc_rank]; i++)
    {
      *(recvbuff_step1 + i) = *(recvbuff_step1 + i) / bcastbuff_step1;
    }

    MPI_Gatherv(recvbuff_step1, elmt_per_proc_step1[proc_rank], MPI_DOUBLE, matrix + pivot * count_y, elmt_per_proc_step1, elmt_offset_step1, MPI_DOUBLE, rootproc, MPI_COMM_WORLD);

    // TODO: Step 2 - Make the upper and lower row to be 0 other than the pivot elmt
    // Prepare pivot row
    if (proc_rank == rootproc)
    {
      memcpy(bcastbuff_step2, matrix + (pivot * count_y), count_y * sizeof(double));
    }

    // Broadcast pivot row and scatter the rest
    MPI_Bcast(&bcastbuff_step2, count_y, MPI_DOUBLE, rootproc, MPI_COMM_WORLD);
    MPI_Scatterv(matrix, elmt_per_proc, elmt_offset, MPI_DOUBLE, recvbuff_step2, elmt_per_proc[proc_rank], MPI_DOUBLE, rootproc, MPI_COMM_WORLD);

    // // Do the substraction operation with the pivot row
    for (int i = 0; i < array_per_proc[proc_rank]; i++)
    {
      if (array_offset[proc_rank] + i == pivot)
        continue;
      double multiplier = *(recvbuff_step2 + i * count_y + pivot) / *(bcastbuff_step2 + pivot);
      for (int j = 0; j < count_y; j++)
      {
        *(recvbuff_step2 + i * count_y + j) = *(recvbuff_step2 + i * count_y + j) - (*(bcastbuff_step2 + j) * multiplier);
      }
    }

    // // Gather the row back together
    MPI_Gatherv(recvbuff_step2, elmt_per_proc[proc_rank], MPI_DOUBLE, matrix, elmt_per_proc, elmt_offset, MPI_DOUBLE, rootproc, MPI_COMM_WORLD);

    // DEBUG purposes only
    if (proc_rank == rootproc)
    {
      cout << "matrix iteration " << pivot + 1  << endl;
      printMatrix(matrix, 6, 3);
      cout << endl;
    }
  }

  MPI_Finalize();
  return 0;
}

/*
int main () {
  double **mat;
  int size;

  readfile(&mat, &size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size * 2; j++) {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }

  clear(mat);

  return 0;
}
*/