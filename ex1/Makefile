#shirat345@gmail.com

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

# Files
SRC_FILES = $(SRC_DIR)/Graph.cpp $(SRC_DIR)/Algorithms.cpp $(SRC_DIR)/Queue.cpp $(SRC_DIR)/PriorityQueue.cpp $(SRC_DIR)/UnionFind.cpp
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_FILE = main.cpp
MAIN_OBJ = $(OBJ_DIR)/main.o
TEST_FILE = test.cpp
TEST_OBJ = $(OBJ_DIR)/test.o

# Executables
EXEC = ex1
TEST_EXEC = test_runner

# Default target
all: $(EXEC)

# Ensure obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Target to build the main project
$(EXEC): $(OBJ_FILES) $(MAIN_OBJ) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ_FILES) $(MAIN_OBJ)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main
$(OBJ_DIR)/main.o: $(MAIN_FILE) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(MAIN_FILE) -o $@

# Compile test file
$(OBJ_DIR)/test.o: $(TEST_FILE) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(TEST_FILE) -o $@

# Build test executable
$(TEST_EXEC): $(OBJ_FILES) $(TEST_OBJ) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(OBJ_FILES) $(TEST_OBJ)

# Run main
main: $(EXEC)
	@./$(EXEC)

# Run tests
test: $(TEST_EXEC)
	@./$(TEST_EXEC)

# Valgrind test
 valgrind: $(EXEC) $(TEST_EXEC)
	valgrind --leak-check=full ./$(EXEC) > /dev/null
	valgrind --leak-check=full ./$(TEST_EXEC) > /dev/null

# Clean
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC) $(TEST_EXEC)

.PHONY: all clean test valgrind main
