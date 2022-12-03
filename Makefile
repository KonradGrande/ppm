CC = gcc
CFLAGS = -Wall -Wextra

ppm.o: ppm.c

clean:
	-rm ppm.o

.phony: clean
