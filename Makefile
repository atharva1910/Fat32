CC = g++
ARGS = -Wall -g -o

all: FAT32.hpp FAT32.o
	$(CC) FAT32.o $(ARGS) FAT32

FAT32.o:FAT32.cc FAT32.hpp
	$(CC) -c -g FAT32.cc
clean:
	rm -r *.o FAT32
