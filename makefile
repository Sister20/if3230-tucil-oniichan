MPI_CC = mpicc
THREADS = 2
OUTPUT_FOLDER = output
BIN_FOLDER = bin


all: serial parallel

parallel: mpi mp

mpi:
	mpic++ src/open-mpi/mpi.cc -o $(BIN_FOLDER)/mpi.exe

mp: 
	g++ src/open-mp/mp.cc --openmp -o $(BIN_FOLDER)/mp

cuda:
	nvcc src/cuda/inverse-matrix.cu src/cuda/cuda.cu -o $(BIN_FOLDER)/cuda.exe

serial:
	g++ src/serial/serial.cpp -o $(BIN_FOLDER)/serial.exe

run:
	time ./bin/serial.exe < test_cases/2048.txt > $(OUTPUT_FOLDER)/output_serial.txt
	time mpiexec -n $(N) ./bin/mpi.exe < test_cases/2048.txt > $(OUTPUT_FOLDER)/output_mpi.txt
	time ./bin/mp < test_cases/1024.txt > $(OUTPUT_FOLDER)/output_mp.txt

run-serial:
	time ./bin/serial.exe < test_cases/2048.txt > $(OUTPUT_FOLDER)/output_serial.txt

run-cuda:
	time ./bin/cuda.exe < test_cases/1024.txt > $(OUTPUT_FOLDER)/output_cuda.txt