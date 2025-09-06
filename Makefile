PROGRAM= mem-play
CC= gcc
STD= -std=c99
CFLAGS= -c -g -Wall -Werror -Wextra
OBJS= x.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM)

%.o: %.c
	$(CC) $(STD) $(CFLAGS) -o $@ $<

x.o: x.c
	
clean:
	rm -f $(OBJS) $(PROGRAM)

.PHONY: all clean
