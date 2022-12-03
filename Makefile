# https://stackoverflow.com/questions/16886591/how-do-i-enable-c11-in-gcc
CXX=g++
CXXFLAGS=-g -std=c++17 -Wall
BIN=prog

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)