#include <cuda_runtime.h>

__global__ void calculateInverse(double* matrix_pointer, int width, int height, int currRow);

__device__ void step1(double* matrix_pointer, int width, int height, int currRow, double diagonal);

__device__ void step2(double* matrix_pointer, int width, int height, int currRow, double diagonal);