all: 	build run
init: 	clean cfg build


build: clean
	cmake --build ./build/
run:
	./main.out
clean:
	rm -rf *.out 
cfg: 	
	cd build/;cmake ../
