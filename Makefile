CXX = g++
CXX_FLAGS = -std=c++17 -Wall


all:	clean compile run
	
	

clean:
	rm -rf *.o
	rm -rf *.out

run:
	./main.out

compile:
	$(CXX) $(CXX_FLAGS) -c src/CubeRotator.cpp src/main.cpp src/vec3.cpp
	$(CXX) $(CXX_FLAGS) -o main.out CubeRotator.o main.o vec3.o