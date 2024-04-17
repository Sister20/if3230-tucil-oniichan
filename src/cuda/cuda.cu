#include <stdio.h>
#include <iostream>
#include "inverse-matrix.cuh"

using namespace std;

// Display a 2d matrix
void printMatrix(double *matrix, int count_width, int count_row, int res)
{
  for (int i = 0; i < count_row; i++)
  {
    for (int j = 0; j < count_width; j++)
    {
      if (res)
      {
        if (j > (count_width / 2) - 1)
        {
          cout << *(matrix + j + i * count_width) << " ";
        }
      }
      else
      {
        cout << *(matrix + j + i * count_width) << " ";
        if (j == (count_width / 2) - 1)
        {
          cout << "|";
        }
      }
    }
    cout << endl;
  }
}

int main(int argc,char **argv)
{
  double *matrix;
  int mat_size;

  cin >> mat_size;
  int count_x = mat_size;
  int count_y = mat_size * 2;
  matrix = (double *)malloc(count_x * count_y * sizeof(double));

  for (int i = 0; i < mat_size; i++)
  {
    for (int j = 0; j < mat_size; j++)
    {
      cin >> *(matrix + i * count_y + j);
    }
  }

  for (int i = 0; i < mat_size; i++)
  {
    for (int j = mat_size; j < (mat_size) * 2; j++)
    {
      if (i + mat_size == j)
      {
        *(matrix + i * count_y + j) = 1;
      }
      else
      {
        *(matrix + i * count_y + j) = 0;
      }
    }
  }


  dim3 blockDim(16);
  dim3 gridDim((count_y + blockDim.x - 1) / blockDim.x);

  double *device_matrix_pointer;

  cudaMalloc((void**)&device_matrix_pointer, count_x * count_y * sizeof(double));
  cudaMemcpy(device_matrix_pointer, matrix,  count_x * count_y * sizeof(double), cudaMemcpyHostToDevice);

  printf("grid.x %d grid.y %d grid.z %d\n",gridDim.x,gridDim.y,gridDim.z);
  printf("block.x %d block.y %d block.z %d\n",blockDim.x,blockDim.y,blockDim.z);

  for (int i = 0; i < count_x; i++) {
    calculateInverse<<<blockDim,gridDim>>>(device_matrix_pointer, count_y, count_x, i);
    cudaDeviceSynchronize();
  }

  cudaMemcpy(matrix, device_matrix_pointer, count_x * count_y * sizeof(double), cudaMemcpyDeviceToHost);

  printMatrix(matrix, count_y, count_x, 0);

  cudaFree(device_matrix_pointer);
  cudaDeviceReset();
  return 0;
}