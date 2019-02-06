# Makefile for Y86 Disassembler
#

CC = g++ -g 

y86dis: y86dis.o
	$(CC) y86dis.o -o y86dis

y86dis.o: y86dis.cpp

clean:
	rm -f *.o
