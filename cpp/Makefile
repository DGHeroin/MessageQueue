objects=main.o
CC=g++
CXXFLAGS= -g -std=c++11

.PHONY: all clean

all:$(objects)
	$(CC) $(objects) -o app $(CXXFLAGS)

clean:
	-rm $(objects) app