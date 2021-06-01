CXX=g++
CXXFLAGS=-Wall -std=c++11 -O2 -lm -Werror -Wno-sign-compare -pedantic
all:solution benchmark
solution: main.o st.o
	$(CXX) $(CXXFLAGS) -o solution main.cpp st.cpp
benchmark: benchmark.o st.o
	$(CXX) $(CXXFLAGS) -o benchmark benchmark.cpp st.cpp
main.o: st.hpp
st.o: st.hpp
benchmark.o: st.hpp
clean: 
	rm -f *.o solution benchmark