CXX = g++
CXX_FLAGS = -std=c++17 -Wall 


all:	clean	compile	run
	
	

clean:
	rm -rf *.o
	rm -rf *.out

run:
	./main.out

compile:
	$(CXX) $(CXX_FLAGS) -c CubeRotator.cpp main.cpp 
	$(CXX) $(CXX_FLAGS) -o main.out CubeRotator.o main.o