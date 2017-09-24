all: project

project: project.cpp
	g++ project.cpp -Wall -oproject -lX11 -lGL -lGLU -lm

clean:
	rm -f project
	rm -f *.o
