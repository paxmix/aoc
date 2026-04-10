CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wpedantic -O2 -Iinclude

TEST_CXXFLAGS = -std=c++23 -O2 -Iinclude

# SOURCES
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

OBJ_NO_MAIN = $(filter-out build/main.o, $(OBJ))
TEST_SRC = tests.cpp
TEST_OBJ = build/tests/tests.o

TARGET = bin/aoc_run
TEST_TARGET = bin/tests

# MAIN BUILD
all: $(TARGET)

# Link
$(TARGET): $(OBJ) | bin
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile
build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# TEST BUILD

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(OBJ_NO_MAIN) $(TEST_OBJ) | bin
	$(CXX) $(TEST_CXXFLAGS) $^ -o $@ -lCatch2Main -lCatch2

build/tests/tests.o: tests.cpp | build/tests
	$(CXX) $(TEST_CXXFLAGS) -c $< -o $@

# ========= FETCH BUILD =========
FETCH_SRC = fetch_puzzles.cpp
FETCH_OBJ = build/fetch_puzzles.o
FETCH_TARGET = bin/fetch

fetch: $(FETCH_TARGET)
		./$(FETCH_TARGET)

$(FETCH_TARGET): $(FETCH_OBJ) | bin
	$(CXX) $(CXXFLAGS) $^ -o $@ -lcurl

$(FETCH_OBJ): $(FETCH_SRC) | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==============================
build:
	mkdir -p build

build/tests:
	mkdir -p build/tests

bin:
	mkdir -p bin

clean:
	rm -rf build bin

.PHONY: all test clean
