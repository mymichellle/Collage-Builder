#!/bin/sh

g++ -g -O3 -I/usr/X11/include -L/usr/X11/lib -lGL -lglut -o Collage *.cpp
#gcc -o myProg myProg.c -I /usr/X11R6/include/ -L /usr/X11R6/lib64/ -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm

#g++ `pkg-config opencv --cflags --libs` *.cpp -o PiMP
