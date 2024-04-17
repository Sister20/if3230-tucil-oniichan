#include <cuda_runtime.h>

__global__ void calculateInverse(double* matrix_pointer, int width, int height, int currRow);

__global__ void step1(double* matrix_pointer, int width, int height, int currRow);

__global__ void step2(double* matrix_pointer, int width, int height, int currRow);