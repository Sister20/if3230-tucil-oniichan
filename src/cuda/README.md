# Parallel Inverse Matrix Algorithm using Gauss-Jordan with Cuda

The provided program implements matrix inversion using GPU acceleration with CUDA. It consists of two main parts: the host code (in cuda.cu) and the device code (in inverse-matrix.cuh and inverse-matrix.cu).

## Algorithm Overview

The provided code implements the inverse matrix calculation using GPU acceleration with CUDA (Compute Unified Device Architecture). The algorithm follows the Gaussian elimination method for finding the inverse of a given matrix.

### Matrix Initialization
In CUDA programming, data parallelism is achieved by dividing the input data into smaller chunks and assigning each chunk to different threads for parallel processing on the GPU. This strategy allows for efficient utilization of the GPU's massively parallel architecture.

### Parallelization Strategy
For each row in the matrix, two CUDA kernels are launched sequentially

1. **Grid and Block Configuration**:The CUDA kernel functions step1 and step2 are launched with a grid of blocks configuration, where each block contains multiple threads. The grid is configured to handle the entire dataset, with each thread responsible for processing a portion of the data.
2. **Thread Indexing**:Within each CUDA kernel, thread indices are used to partition the data. For example, in the step1 kernel, each thread processes a subset of the matrix elements along a row, dividing the workload among multiple threads. 
3. **Shared Memory Usage**: Shared memory can be utilized for data partitioning and communication among threads within the same block. However, in the provided code, shared memory usage is limited, and global memory is primarily used for data access.

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