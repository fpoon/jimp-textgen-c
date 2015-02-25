# Makefile
# Created on: 25 lut 2015
#     Author: mariusz

CC=gcc
LIBS=
OBJS=main.o settings.o utilities.o

.PHONY: all clean

textgen: $(OBJS)
		$(CC) $(OBJS) -o textgen
		
main.o:
	cc -c src/main.c

settings.o:
	cc -c src/settings.c
	
utilities.o:
	cc -c src/utilities.c

all: textgen

clean:
	rm -rf *.o textgen