# Parallel Inverse Matrix Algorithm using Gauss-Jordan with Cuda

This README provides a comprehensive overview of an algorithm for efficiently computing the inverse of a matrix using the Gauss-Jordan method with MPI (Message Passing Interface) for parallelization. The algorithm divides the Gauss-Jordan elimination into two major steps that can be parallelized, significantly improving computational efficiency.

## Algorithm Overview

The provided code implements the inverse matrix calculation using GPU acceleration with CUDA (Compute Unified Device Architecture). The algorithm follows the Gaussian elimination method for finding the inverse of a given matrix.

### Matrix Initialization
The algorithm first prepares the input matrix for inversion. It appends an identity matrix of the same size to the right of the input matrix. This augmented matrix is then loaded onto the GPU.

### Parallelization Strategy
For each row in the matrix, two CUDA kernels are launched sequentially

1. **Parallelization - Step 1: Dividing the Pivot Row**: This kernel divides each element in the current row by the diagonal element of that row, making the diagonal element equal to 1.

2. **Parallelization - Step 2: Eliminating Upper and Lower Elements**: This kernel performs the row reduction operations to make all elements above and below the diagonal in the current column zero.

## Running the Algorithm
To run the algorithm:
1. Compile the CUDA code using an appropriate compiler. Ensure that you have CUDA toolkit installed and configured properly.
2. Execute the compiled executable, providing the size of the matrix and its elements as input.

## Notes
- Ensure that the CUDA toolkit is correctly installed and configured on your system.
- The code assumes that the CUDA device has sufficient resources to accommodate the matrix and perform the required computations.
- This implementation focuses on simplicity and may not be optimized for performance. Depending on the size of the matrix, more sophisticated techniques may be required for efficiency.

## References
- [Gauss-Jordan elimination](https://en.wikipedia.org/wiki/Gauss%E2%80%93Jordan_elimination)
- [NVIDIA CUDA Toolkit Documentation](https://docs.nvidia.com/cuda/index.html)