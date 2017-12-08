all: project

project: project.h project.cpp main.cpp
	g++ project.cpp main.cpp  -Wall -opong -lX11 -lGL -lGLU -lglut -lm

clean:
	rm -f project
	rm -f pong
	rm -f *.o
