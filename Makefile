CXX = g++
CXX_FLAGS = -std=c++17 -Wall 


all:
	$(CXX) $(CXX_FLAGS) -c CubeRotator.cpp main.cpp 
	$(CXX) $(CXX_FLAGS) -o main.out CubeRotator.o main.o

clean:
	rm -rf *.o
	rm -rf *.out

