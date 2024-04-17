#include <stdio.h>
#include "inverse-matrix.cuh"

using namespace std;

__global__ void calculateInverse(double *matrix_pointer, int width, int height, int currRow)
{
  __shared__ double diagonal;
  diagonal = matrix_pointer[width * currRow + currRow];
  __syncthreads();

  // step1(matrix_pointer, width, height, currRow, diagonal);
  __syncthreads();
  // step2(matrix_pointer, width, height, currRow, diagonal);
}

__global__ void step1(double *matrix_pointer, int width, int height, int currRow)
{
  __shared__ double diagonal;
  diagonal = matrix_pointer[width * currRow + currRow];
  __syncthreads();

  int idx = blockIdx.x * blockDim.x + threadIdx.x;

  if (idx < width)
  {
    matrix_pointer[currRow * width + idx] = matrix_pointer[currRow * width + idx] / diagonal;
  }
  __syncthreads();
}

__global__ void step2(double *matrix_pointer, int width, int height, int currRow)
{
  int row_idx = blockIdx.x * blockDim.x + threadIdx.x;
  __syncthreads();
  // int col_idx = blockIdx.y * blockDim.y + threadIdx.y;

  // if (row_idx != currRow && row_idx < height && col_idx < width && col_idx >= currRow) {
  //     int pivotAdjIdx = row_idx * width + currRow;
  //     double multiplier = matrix_pointer[pivotAdjIdx];

  //     int idx = row_idx * width + col_idx;
  //     int pivotIdx = currRow * width + col_idx;

  //     double before = matrix_pointer[idx];
  //     double pivotElmt = matrix_pointer[pivotIdx];

  //     matrix_pointer[idx] = before - multiplier * pivotElmt;

  //     // double after = matrix_pointer[idx];

  //     // printf("iteration: %d, Col: %d, Row: %d, Multiplier: %.15f, pivotElmt %.15f, before %.15f, after %.15f, height %d width %d\n", currRow, col_idx, row_idx, multiplier, pivotElmt, before, after, height, width);
  // }

  if (row_idx != currRow && row_idx < height)
  {
    // printf("Row: %d\n", row_idx);
    int pivotAdjIdx = row_idx * width + currRow;
    double multiplier = matrix_pointer[pivotAdjIdx];
    for (int col = 0; col < width; col++)
    {
      int idx = row_idx * width + col;
      int pivotIdx = currRow * width + col;

      double before = matrix_pointer[idx];
      double pivotElmt = matrix_pointer[pivotIdx];

      matrix_pointer[idx] = before - multiplier * pivotElmt;

      double after = matrix_pointer[idx];

      // printf("iteration: %d, Col: %d, Row: %d, Multiplier: %.15f, pivotElmt %.15f, before %.15f, after %.15f, height %d width %d\n", currRow, col, row_idx, multiplier, pivotElmt, before, after, height, width);
    }
  }
  __syncthreads();
}