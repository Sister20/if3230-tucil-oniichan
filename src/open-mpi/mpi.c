#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int n;
    double m[n][2 * n];

    if (argc < 2) {
        exit(1);
    }

    // Position to be turned into 1
    int pivot = 0;

    // Initialize world rank and world size
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_Comm_rank, &world_rank);

    // Divide the pivot row elements
    // Scatter all row elements

    double top_num;
    MPI_Scatter(
        m[pivot],
        1,
        MPI_DOUBLE,
        &top_num,
        1,
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD
    );

    // Braodcast pivot element

    double bottom_num;

    if (world_rank == 0) {
        bottom_num = m[pivot][pivot];
    }

    MPI_Bcast(
        &bottom_num,
        1,
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD
    );

    double result = top_num / bottom_num;

    double *pivot_row;

    if (world_rank == 0) {
        pivot_row = malloc(sizeof(MPI_DOUBLE) * (2 * n));
    }

    

    // Substract all other rows with the pivot row
}