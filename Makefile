# Compiler settings
CXX = g++-14
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -Iinclude/pieces

# Directories
SRC_DIR = src
PIECE_SRC_DIR = $(SRC_DIR)/pieces
BUILD_DIR = build
PIECE_BUILD_DIR = $(BUILD_DIR)/pieces

# Find all .cpp files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(PIECE_SRC_DIR)/*.cpp)

# Create matching .o file paths in build/
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, \
       $(patsubst $(PIECE_SRC_DIR)/%.cpp, $(PIECE_BUILD_DIR)/%.o, $(SRCS)))

# Executable name
TARGET = run

.PHONY: all clean

all: $(TARGET)

# Link all object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile src/*.cpp into build/*.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile src/pieces/*.cpp into build/pieces/*.o
$(PIECE_BUILD_DIR)/%.o: $(PIECE_SRC_DIR)/%.cpp
	@mkdir -p $(PIECE_BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)