GCC=gcc
LIBS= -lX11 -lGL -lGLEW -lm -lpthread
FLAGS= -Wall -pedantic

all: main

%.o: %.c %.h
	$(GCC) $(FLAGS) -c -o $@ $<

main:	window.o \
		textureRGB.o textureRGBA.o \
		cube.o ball.o axis.o intersect.o\
		mat.o util.o\
		program.o \
		text.o font.o\
		drawVert.o\
		eye.o\
		keymanager.o\
		list.o \
		xWin.o main.o
	$(GCC) $(FLAGS) $(LIBS) $^ -o main


clean:
	rm -f *.o main
	clear

