#Makefile
#Autor Lucas Azevedo
PROG = main
CC = g++
CPPFLAGS = -O0 -g -ansi -Wall -pedantic -std=c++17
OBJS = main.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o: main.cpp hashtable.h
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm -f $(PROG) $(OBJS)