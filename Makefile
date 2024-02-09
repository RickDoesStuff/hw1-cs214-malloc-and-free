# Define the compiler
CC=gcc

# Compiler flags
CFLAGS=-Wall -g

# Debugging flags
DFLAGS=-Wall -g -DDEBUG

# Define the target executable name
TARGET=memgrind

# List of source files
SOURCES=chunkhead.c chunk.c mymalloc.c memgrind.c

# Object files to generate
OBJECTS=$(SOURCES:.c=.o)

# Default rule to build the program
all: $(TARGET)

# Debug rule to build the program with debug flags
debug: CFLAGS = $(DFLAGS)
debug: $(TARGET)

# Rule for linking the program
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for compiling source files to object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

# Special case for memgrind.c which might not need a memgrind.h
memgrind.o: memgrind.c
	$(CC) $(CFLAGS) -c $<

# Rule for cleaning up
clean:
	del -f $(OBJECTS) $(TARGET).exe

# Dependencies
chunkhead.o: chunkhead.c chunkhead.h
chunk.o: chunk.c chunk.h
mymalloc.o: mymalloc.c mymalloc.h
memgrind.o: memgrind.c memgrind.h # Add this line if memgrind.h exists and is used
