# Parallel Inverse Matrix Algorithm using Gauss-Jordan with MPI

The provided code implements matrix inversion using Gauss-Jordan Elimination, a numerical method to find the inverse of a matrix. OpenMP, a parallel computing API, is utilized for parallelization to enhance performance.

## Algorithm Overview

The algorithm follows these steps:

1. **Input**: The user inputs the size of the square matrix n followed by the coefficients of the matrix.

2. **Memory Allocation**: Memory is allocated for a 2D array to store the matrix and its augmented form.

3. **Partial Pivoting**: Partial pivoting is performed to improve numerical stability. However, this part is currently commented out in the code.

4. **Reducing to Diagonal Matrix**: The algorithm iterates over each row, excluding the diagonal, and reduces the elements to form a diagonal matrix.

5. **Reducing to Unit Matrix**: Each row is scaled such that the diagonal elements become 1, resulting in the inverse matrix.

6. **Output**: The program prints the execution time, size of the matrix n, and the inverse matrix.

## Running the Algorithm
To run the algorithm, follow these steps:

1. Compile the code using an appropriate compiler supporting OpenMP, such as GCC or Clang.
2. Execute the compiled binary, providing the matrix size n and its coefficients as input

## Notes
- OpenMP directives are used for parallelization to leverage multi-core CPUs.
- Partial pivoting, although commented out, can be enabled for improved numerical stability.
- This implementation assumes that the input matrix is invertible and does not handle singular matrices.

## References
- [Gauss-Jordan elimination](https://en.wikipedia.org/wiki/Gauss%E2%80%93Jordan_elimination)
- [OpenMP Documentation](https://www.openmp.org/)