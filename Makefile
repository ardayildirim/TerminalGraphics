CXX = g++
CXX_FLAGS = -std=c++17 -Wall


all:	clean compile run
	


clean:
	rm -rf *.o

run:
	./main.out

compile:
	$(CXX) $(CXX_FLAGS) -c src/main.cpp src/vec3.cpp src/Scene1.cpp src/Scene2.cpp src/Scene3.cpp src/Scene4.cpp
	$(CXX) $(CXX_FLAGS) -o main.out main.o vec3.o Scene1.o Scene2.o Scene3.o Scene4.o
	rm -rf *.o