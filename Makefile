all: build run
init: clean cfg build


build: clean
	cmake --build ./build/

run:
	./main.out

make cfg:
	cd build/;cmake ../

clean:
	rm -rf *.out 

deleteO:
	rm -rf *.o

g++: clean compileg++ run

compileg++:
	g++ -c src/vec3.cpp src/main.cpp src/Scene1.cpp src/Scene2.cpp src/Scene3.cpp src/Scene4.cpp src/Scene5.cpp -std=c++17 -Wall
	g++ -o main.out vec3.o main.o Scene1.o Scene2.o Scene3.o Scene4.o Scene5.o -std=c++17 -Wall