# Compiler and linker.
CC=g++

# Name of the executable.
TARGET=libutils.so

# Compiler flags.
CCFLAGS=-g -fPIC -Wall -std=c++17

# List all the sources needed for this project.
SOURCES=$(wildcard *.cpp)

# List the objects needed for the project (all come
# from the list in SOURCES).
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

# List dependency files, one for each source file.
DEPENDS=$(patsubst %.cpp,%.d,$(SOURCES))

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -fPIC -shared -o $(TARGET)

-include $(DEPENDS)

%.o: %.cpp Makefile
	$(CC) $(CCFLAGS) -MMD -MP -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)