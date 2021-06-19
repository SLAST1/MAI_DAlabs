CXX=g++
CXXFLAGS=-Wall -std=c++11 -O2 -lm -Werror -Wno-sign-compare -pedantic
all:solution benchmark
solution: main.o bigint.o
	$(CXX) $(CXXFLAGS) -o solution main.cpp bigint.cpp
benchmark: benchmark.o bigint.o
	$(CXX) $(CXXFLAGS) -o benchmark benchmark.cpp bigint.cpp -lgmp -lgmpxx
main.o: bigint.hpp
bigint.o: bigint.hpp
benchmark.o: bigint.hpp
clean: 
	rm -f *.o solution