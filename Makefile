CC = g++
CFLAGS = -Wall -g
CXXFLAGS = $(CFLAGS)
INCLUDE = ./include/
LIBS = -lGL -lGLEW -lglfw


all: main.o Display.o Input.o Util.o Shader.o Camera.o
	$(CC) $(CXXFLAGS) Util.o Input.o main.o Shader.o Display.o Camera.o -o simpleRenderer.elf $(LIBS)

main.o: src/main.cpp
	$(CC) -I $(INCLUDE) -c src/main.cpp $(CXXFLAGS) -o main.o

Display.o: src/Display.cpp
	$(CC) -I $(INCLUDE) -c src/Display.cpp $(CXXFLAGS) -o Display.o

Input.o: src/Input.cpp
	$(CC) -I $(INCLUDE) -c src/Input.cpp $(CXXFLAGS) -o Input.o

Util.o: src/Util.cpp
	$(CC) -I $(INCLUDE) -c src/Util.cpp $(CXXFLAGS) -o Util.o

Shader.o: src/Shader.cpp
	$(CC) -I $(INCLUDE) -c src/Shader.cpp $(CXXFLAGS) -o Shader.o

Camera.o: src/Camera.cpp
	$(CC) -I $(INCLUDE) -c src/Camera.cpp $(CXXFLAGS) -o Camera.o

.PHONY: clean

clean:
	rm *.o *.elf
