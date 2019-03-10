CC = c99
CFLAGS = -Wall -O2

# LIB = -lpthread

all: tiny

tiny: tiny.c misc.c file_proc.c file_proc.h misc.h
	$(CC) $(CFLAGS) -o tiny tiny.c misc.c file_proc.c $(LIB)

clean:
	rm -f *.o tiny *~
