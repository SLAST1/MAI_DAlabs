CXX=g++
CXXFLAGS=-Wall -std=c++11 -O2 -lm -Werror -Wno-sign-compare -pedantic
all:solution
solution: main.o johnson.o
	$(CXX) $(CXXFLAGS) -o solution main.cpp johnson.cpp
main.o: structures.hpp johnson.hpp
johnson.o: structures.hpp johnson.hpp
clean: 
	rm -f *.o solution