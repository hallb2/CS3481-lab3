CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CPP = $(CXX) $(CXXFLAGS)

OBJ = y86dis.o instruction.o

main: $(OBJ)
	$(CPP) $(OBJ) -o main

y86dis.o: y86dis.cpp

instruction.o: instruction.cpp instruction.h  

clean:
	rm -f *.o
