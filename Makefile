

CC=g++
CFLAGS=-Wall -g -std=c++11
OBJ=main.o camera_simple.o math_functions.o screen.o color.o ray.o precision_epsilon.o scene.o square.o

.PHONY: all

all: raytracer

clean:
	rm raytracer $(OBJ)

run: raytracer
	./raytracer

raytracer: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@


main.o: main.cpp
	$(CC) -c $(CFLAGS) $? -o $@


scene.o: scene.cpp
	$(CC) -c $(CFLAGS) $? -o $@


camera_simple.o: camera_simple.cpp
	$(CC) -c $(CFLAGS) $? -o $@


math_functions.o: math_functions.cpp
	$(CC) -c $(CFLAGS) $? -o $@


screen.o: screen.cpp
	$(CC) -c $(CFLAGS) $? -o $@


color.o: color.cpp
	$(CC) -c $(CFLAGS) $? -o $@


ray.o: ray.cpp
	$(CC) -c $(CFLAGS) $? -o $@


precision_epsilon.o: precision_epsilon.cpp
	$(CC) -c $(CFLAGS) $? -o $@


square.o: square.cpp
	$(CC) -c $(CFLAGS) $? -o $@
