# Mem-play #

PROGRAM= mplay
CC= gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -pedantic -std=c99

BUILD ?= debug

SRC= main.c mem_chunk.c
OBJS= $(SRC:%.c=%.o) # grabs the src variable and replaces c's with o's
DEPS= $(OBJS:%.o=%.d) # same as above

ifeq ($(BUILD),release)
    CFLAGS += -O2 -DNDEBUG
else ifeq ($(BUILD),debug)
    CFLAGS += -g -O0 -DDEBUG
else
    $(error Invalid BUILD value. Use 'debug' or 'release')
endif

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

-include $(DEPS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean: # make clean after running and debugging for example
	rm -f $(OBJS) $(DEPS) $(PROGRAM)

debug:
	$(MAKE) BUILD=debug

release:
	$(MAKE) BUILD=release

config:
	@echo "Program: $(PROGRAM)"
	@echo "Current build: $(BUILD)"
	@echo "CFLAGS: $(CFLAGS)"

.PHONY: all clean debug release config