CXX ?= g++
CX ?= gcc
CFLAGS = -Wall -Wconversion -std=c++0x -O3 -fPIC -I./
main: kernel_lsh.o main.cc
	$(CXX) $(CFLAGS) -o main main.cc kernel_lsh.o

kernel_lsh.o: kernel_lsh.cc kernel_lsh.h
	$(CXX) $(CFLAGS) -c -o kernel_lsh.o kernel_lsh.cc
clean:
	rm kernel_lsh.o
