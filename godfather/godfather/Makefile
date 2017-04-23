CXX = g++
CXXFLAGS = -Wall -g -std=c++11
EXE = godfather

build: main.o airport.o structure.o input.o
	$(CXX) $(CXXFLAGS) main.o airport.o structure.o input.o -o $(EXE)

main.o: main.cpp
airport.o: airport.cpp
structure.o: structure.cpp
input.o: input.cpp

tags:
	ctags *.cpp *.h

clean:
	rm *.o $(EXE)
