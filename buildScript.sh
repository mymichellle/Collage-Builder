#!/bin/sh

g++ -g -O3 -I/usr/X11/include -L/usr/X11/lib -framework GLUI   -lGL -lglut -o Collage *.cpp *.c 
#gcc -o myProg *.c -I /usr/X11R6/include/ -L /usr/X11R6/lib64/ -lglut -lGL -lglut -lGLU -lX11 -lXmu -lXi -lm


