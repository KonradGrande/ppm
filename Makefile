CC = gcc
CFLAGS = -Wall -Wextra -ggdb

ppm.o: ppm.c

clean:
	-rm ppm.o

.phony: clean
