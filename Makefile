CC = g++
CFLAGS = -Wall -g
 

Controller: Controller.o Definitions.o
Controller.o: Controller.cpp Controller.h Definitions.h
Definitions.o: Definitions.cpp Definitions.h
