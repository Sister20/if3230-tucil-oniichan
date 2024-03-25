# Parallel Inverse Matrix Algorithm using Gauss-Jordan with MPI

This README provides a comprehensive overview of an algorithm for efficiently computing the inverse of a matrix using the Gauss-Jordan method with MPI (Message Passing Interface) for parallelization. The algorithm divides the Gauss-Jordan elimination into two major steps that can be parallelized, significantly improving computational efficiency.

## Algorithm Overview

The algorithm follows these steps:

### Matrix Initialization
- Read the input matrix of size `matrix_size x matrix_size`.
- Expand the matrix to size `matrix_size x 2*matrix_size` to accommodate the right-hand side identity matrix.
- Iterate through the matrix, selecting the i-th row as the pivot row and the i-th element of that row as the pivot element.

### Parallelization Strategy
The Gauss-Jordan elimination algorithm is divided into two parallelizable steps: dividing the pivot row and eliminating upper and lower elements.

1. **Parallelization - Step 1: Dividing the Pivot Row**
   - To parallelize this step, the pivot row is divided among the available processes.
   - Each process receives approximately `2*matrix_size/n_process` elements of the pivot row to ensure load balancing and minimize communication overhead. 
   - Each received element is divided by the pivot element.

2. **Parallelization - Step 2: Eliminating Upper and Lower Elements**
   - To parallelize this step, the matrix is divided among the available processes.
   - Each process receives approximately `matrix_size/n_process` rows of the matrix.
   - Each process ensures that the elements above and below the pivot element become zero.

## Running the Algorithm
To run the algorithm, follow these steps:

1. **Prerequisites**
   - Ensure you have a working MPI installation and a compatible C/C++ compiler for compilation.
   - Install any necessary dependencies or libraries required for MPI.

2. **Compilation**
   - Compile the program using the provided Makefile:
     ```bash
     make mpi
     ```
   - The binary file will be created inside the `bin` folder.

3. **Execution**
   - Execute the compiled program using an MPI launcher. For example, using `mpirun`:
     ```
     mpirun -np <num_processes> ./bin/mpi.exe < test_cases/2048.txt
     ```
     Replace `<num_processes>` with the desired number of MPI processes.

4. **Result**
   - The program will distribute the computation among the processes, perform the Gauss-Jordan elimination in parallel, and collect the results to obtain the inverse matrix.
   - The output can be directed to the console or written to a file, depending on the implementation.

## Notes
- The algorithm assumes that the input matrix has an inverse. If the matrix is singular or ill-conditioned, the algorithm may produce incorrect results.
- Ensure that the input matrix file follows the specified format to prevent any parsing errors (check `test_cases` foler).

## References
- [Gauss-Jordan elimination](https://en.wikipedia.org/wiki/Gauss%E2%80%93Jordan_elimination)
- [MPI - Message Passing Interface](https://www.mpi-forum.org/)