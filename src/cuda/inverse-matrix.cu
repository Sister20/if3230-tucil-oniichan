#include <stdio.h>
#include "inverse-matrix.cuh"

using namespace std;

__global__ void calculateInverse(double* matrix_pointer, int width, int height, int currRow)
{
  __shared__ double diagonal;
  diagonal = matrix_pointer[width * currRow + currRow];
  __syncthreads();

  step1(matrix_pointer, width, height, currRow, diagonal);
  __syncthreads();
  step2(matrix_pointer, width, height, currRow, diagonal);
}

__device__ void step1(double* matrix_pointer, int width, int height, int currRow, double diagonal) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;

  if (idx < width) {
    matrix_pointer[currRow * width + idx] =  matrix_pointer[currRow * width + idx] / diagonal;
  }

}

__device__ void step2(double* matrix_pointer, int width, int height, int currRow, double diagonal) {
  int row_idx = blockIdx.x * blockDim.x + threadIdx.x;
  int col_idx = blockIdx.y * blockDim.y + threadIdx.y;

  if (row_idx != currRow && row_idx < height && col_idx < width) {
//     // printf("Row: %d\n", row_idx);
//     // int pivotAdjIdx = row_idx * width + currRow;
//     // double multiplier = matrix_pointer[pivotAdjIdx];
//     // for (int col = 0; col < width; col++) {
//     //   int idx = row_idx * width + col;
//     //   int pivotIdx = currRow * width + col;
//     //   matrix_pointer[idx] = matrix_pointer[idx] - multiplier * matrix_pointer[pivotIdx];
//     // }
    double multiplier = matrix_pointer[row_idx * width + currRow];
    printf("Multiplier: %.15f\n", multiplier);
//     int idx = row_idx * width + col_idx;
//     matrix_pointer[idx] = matrix_pointer[idx] - multiplier * matrix_pointer[currRow * width + col_idx];
  }

}