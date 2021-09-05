# Compiler and linker
CC=g++

# Names of executable targets
TARGET=run
TEST_TARGET=test/runtest

# Compiler flags
CCFLAGS=-g -Wall -std=c++17 -I./utils
TEST_CCFLAGS=-g -Wall -std=c++17 -I./utils -I./src
TEST_LDFLAGS=-lcppunit

# Lists of needed sources
SOURCES=$(wildcard src/*.cpp) $(wildcard utils/*.cpp)
TEST_SOURCES=$(wildcard test/*.cpp) $(filter-out src/main.cpp, $(SOURCES))

# Lists of objects needed, defined by sources
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
TEST_OBJECTS=$(patsubst %.cpp,%.o,$(TEST_SOURCES))

# Lists of dependency files, one per source file
DEPENDS=$(patsubst %.cpp,%.d,$(SOURCES))
TEST_DEPENDS=$(patsubst %.cpp,%.d,$(TEST_SOURCES))

.PHONY: all check clean

all: $(TARGET)

check: $(TEST_TARGET)
	./test/runtest

$(TARGET): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(TARGET)

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $(TEST_CCFLAGS) $(TEST_OBJECTS) -o $(TEST_TARGET) $(TEST_LDFLAGS)

-include $(DEPENDS)

%.o: %.cpp Makefile
	$(CC) $(CCFLAGS) -MMD -MP -c $< -o $@

test/%.o: test/%.cpp Makefile
	$(CC) $(TEST_CCFLAGS) -MMD -MP -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)
	-rm -f $(TEST_OBJECTS) $(TEST_DEPENDS) $(TEST_TARGET)
