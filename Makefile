# Compiler and linker.
CC=g++

# Names of normal and test executables.
TARGET=run
TEST_TARGET=test/runtest

# Compiler flags.
CCFLAGS=-g -Wall -std=c++17 -I../utils
TEST_CCFLAGS=-g -Wall -std=c++17 -I../utils -I$(shell pwd)

# Library linking flags.
LIBPATH_UTILS=../utils
LDFLAGS=-L$(LIBPATH_UTILS) -laocutils -lcppunit

# Lists of needed sources.
SOURCES=$(filter-out main.cpp, $(wildcard *.cpp))
TEST_SOURCES=$(wildcard test/*.cpp)

# Lists of objects needed, defined by sources.
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
TEST_OBJECTS=$(patsubst test/%.cpp,test/%.o,$(TEST_SOURCES))

# Lists of dependency files, one for source file.
DEPENDS=main.d $(patsubst %.cpp,%.d,$(SOURCES))
TEST_DEPENDS=$(patsubst test/%.cpp,test/%.d,$(TEST_SOURCES)) $(patsubst %.cpp,%.d,$(SOURCES))

.PHONY: all check clean

all: $(TARGET)

check: $(TEST_TARGET)
	./test/runtest

$(TARGET): main.o $(OBJECTS)
	$(CC) $(CCFLAGS) main.o $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJECTS) $(TARGET)
	$(CC) $(TEST_CCFLAGS) $(OBJECTS) $(TEST_OBJECTS) -o $(TEST_TARGET) $(LDFLAGS)

-include $(DEPENDS)

%.o: %.cpp Makefile
	$(CC) $(CCFLAGS) -fPIC -MMD -MP -c $< -o $@

test/%.o: test/%.cpp Makefile
	$(CC) $(TEST_CCFLAGS) -MMD -MP -c $< -o $@

clean:
	-rm -f main.o $(OBJECTS) $(DEPENDS) $(TARGET) \
	$(TEST_OBJECTS) $(TEST_DEPENDS) $(TEST_TARGET)
