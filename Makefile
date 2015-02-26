# Makefile
# Created on: 25 lut 2015
#     Author: mariusz

CC=gcc
CFLAGS=-g
LDFLAGS=
LIBS=
MACROS=-D_DEBUG
OBJS=main.o settings.o utilities.o

.PHONY: all clean

textgen: $(OBJS)
		$(CC) $(CFLAGS) $(MACROS) $(OBJS) -o textgen $(LDFLAGS) $(LIBS)
		
main.o: src/main.c
	$(CC) $(CFLAGS) $(MACROS) -c src/main.c

settings.o: src/settings.c
	$(CC) $(CFLAGS) $(MACROS) -c src/settings.c
	
utilities.o: src/utilities.c
	$(CC) $(CFLAGS) $(MACROS) -c src/utilities.c

all: textgen

clean:
	rm -rf *.o textgen