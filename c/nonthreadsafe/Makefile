objects=main.o list.o
CC=gcc -g
CXXFLAGS= -g
.PHONY: all clean

all:$(objects)
	$(CC) $(objects) -o app $(CXXFLAGS)

clean:
	-rm $(objects) app