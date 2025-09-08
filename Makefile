# Mem-play #

PROGRAM= mplay
CC= gcc
CPPFLAGS= -MMD #MAKE SPECIFIC FOR DEPENDENCIES
CFLAGS= -Wall -Wextra -pedantic -std=c99
LDFLAGS =
LDLIBS= -lncurses -lpanel

##########################################################
#LDFLAGS:                                                #
#        Linker options and library search paths         #  
#        (e.g., -L/usr/local/lib, -fsanitize=address)    #
#LDLIBS:																								 #
#        Actual libraries to link (e.g., -lm, -lpthread) #
##########################################################
#		[DEBUG BUILD] ADD THESE IF NEEDED -> else ifeq ($(BUILD),debug)
# CFLAGS += -fsanitize=address -fsanitize=undefined 
# LDFLAGS += -fsanitize=address -fsanitize=undefined

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

$(PROGRAM): $(OBJS)                     # or [ $@ ] for program name
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(PROGRAM) 
 # REMEMBER NO CFLAGS DURING LINKING! (not all of them at least)
 #The only time you need CFLAGS in linking is for special cases like:

 #Sanitizers (-fsanitize=address)
 #Link-time optimization (-flto)
 #Profile-guided optimization

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
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "LDLIBS: $(LDLIBS)"

.PHONY: all clean debug release config