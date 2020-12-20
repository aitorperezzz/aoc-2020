# Compiler and linker.
CC=g++

# Name of the executable.
TARGET=run

# Compiler flags.
CCFLAGS=-g -Wall -std=c++17 -I../utils

# Library linking flags
LIBPATH=../utils
LDFLAGS=-L$(LIBPATH) -lutils

# List all the sources needed for this project.
SOURCES=$(wildcard *.cpp)

# List the objects needed for the project (all come
# from the list in SOURCES).
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

# List dependency files, one for each source file.
DEPENDS=$(patsubst %.cpp,%.d,$(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

-include $(DEPENDS)

%.o: %.cpp Makefile
	$(CC) $(CCFLAGS) -MMD -MP -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)
