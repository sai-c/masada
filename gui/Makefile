# https://stackoverflow.com/questions/16886591/how-do-i-enable-c11-in-gcc
WX_CXXFLAGS := $(shell wx-config --cxxflags)
WX_LIBS := $(shell wx-config --libs)

CXX=g++
CXXFLAGS=-g -std=c++17 -Wall $(WX_CXXFLAGS) -I..
BIN=prog

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o) ../FileVault.o ../Definitions.o ../HashingDetectionEngine.o ../PatternMatchingDetectionEngine.o ../Scanner.o ../Logger.o ../VirusHandler.o ../Controller.o


all: $(OBJ)
	$(CXX) -o $(BIN) $^ -lpthread $(WX_LIBS)

%.o: %.c
	$(CXX) $@ -c $< $(WX_CXXFLAGS)

clean:
	rm -f *.o
	rm $(BIN)
