MPI_CC = mpicc
THREADS = 2
OUTPUT_FOLDER = bin

all: serial parallel

parallel:
	mpic++ src/open-mpi/mpi.cc -o $(OUTPUT_FOLDER)/mpi.exe

serial:
	g++ src/serial/serial.cpp -o $(OUTPUT_FOLDER)/serial.exe