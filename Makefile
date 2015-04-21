# Makefile
# Created on: 25 lut 2015
#     Author: mariusz

CC=gcc
CFLAGS= -O3
LDFLAGS=
LIBS=
#MACROS=-D_DEBUG
MACROS=
OBJS=main.o settings.o utilities.o markov.o database.o traintextanal.o ngrams.o

# .PHONY: all clean
all: textgen

textgen: $(OBJS)
		$(CC) $(CFLAGS) $(MACROS) $(OBJS) -o textgen $(LDFLAGS) $(LIBS)
		
main.o: src/main.c
	$(CC) $(CFLAGS) $(MACROS) -c src/main.c

settings.o: src/settings.c
	$(CC) $(CFLAGS) $(MACROS) -c src/settings.c
	
utilities.o: src/utilities.c
	$(CC) $(CFLAGS) $(MACROS) -c src/utilities.c
	
markov.o: src/markov.c
	$(CC) $(CFLAGS) $(MACROS) -c src/markov.c

database.o: src/database.c
	$(CC) $(CFLAGS) $(MACROS) -c src/database.c
	
traintextanal.o: src/traintextanal.c
	$(CC) $(CFLAGS) $(MACROS) -c src/traintextanal.c
	
ngrams.o: src/ngrams.c
	$(CC) $(CFLAGS) $(MACROS) -c src/ngrams.c

clean:
	rm -rf *.o textgen