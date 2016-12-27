CC = g++
ARGS = -Wall -g -o

all:Writing.o Reading.o	main.o
	$(CC) main.o Writing.o Reading.o $(ARGS) FAT32

Writing.o:Writing.hpp main.hpp Writing.cc 
	$(CC) -c  Writing.cc

Reading.o:Reading.hpp main.hpp Reading.cc
	$(CC) -c Reading.cc

main.o:main.hpp main.cc
	$(CC) -c main.cc
clean:
	rm -r *.o FAT32
