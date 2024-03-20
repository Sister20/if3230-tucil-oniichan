OUTPUT_FOLDER = bin

all: serial parallel

parallel:
	mpic++ src/open-mpi/mpi.cc -o mpi.exe

serial:
	g++ src/serial/serial.cpp -o $(OUTPUT_FOLDER)/serial