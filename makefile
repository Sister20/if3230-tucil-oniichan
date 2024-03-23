MPI_CC = mpicc
THREADS = 2
OUTPUT_FOLDER = output
BIN_FOLDER = bin


all: serial parallel

parallel:
	mpic++ src/open-mpi/mpi.cc -o $(BIN_FOLDER)/mpi.exe

serial:
	g++ src/serial/serial.cpp -o $(BIN_FOLDER)/serial.exe

run:  serial parallel
	time ./bin/serial.exe < test_cases/1024.txt > $(OUTPUT_FOLDER)/output_serial.txt
	time mpiexec -n $(N) ./bin/mpi.exe < test_cases/1024.txt > $(OUTPUT_FOLDER)/output_mpi.txt