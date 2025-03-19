# Compiler and flags
CXX := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -O3 -std=c++20
LDFLAGS := -L/usr/lib -lstdc++ -lm

# Directory structure
BUILD_DIR := ./build
SRC_DIR := ./src
INCLUDE_DIR := ./include

# Target executable (now in root directory)
TARGET := inf1010-tp

# Source files and objects
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEP_FILES := $(OBJ_FILES:.o=.d)

# Include directories
INCLUDES := -I$(INCLUDE_DIR)

# Default target
all: $(TARGET)

# Rule for compiling source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Rule for linking the final executable (now in root directory)
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Include generated dependency files
-include $(DEP_FILES)

.PHONY: all clean run remise

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Create submission zip
remise:
	zip -r inf1010-tp.zip $(SRC_DIR)/ $(INCLUDE_DIR)/ Makefile distance.txt