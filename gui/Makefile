WX_CXXFLAGS := $(shell wx-config --cxxflags)
WX_LIBS := $(shell wx-config --libs)

main: main.o mainwindow.o       
	g++ -o main main.o mainwindow.o $(WX_LIBS)

main.o: main.cpp        
	g++ -c main.cpp $(WX_CXXFLAGS)

mainwindow.o: mainwindow.cpp    
	g++ -c mainwindow.cpp $(WX_CXXFLAGS)
