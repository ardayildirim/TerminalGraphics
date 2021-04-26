all: build run

build: clean
	cmake --build ./build/

run:
	./main.out

clean:
	rm -rf *.out 
