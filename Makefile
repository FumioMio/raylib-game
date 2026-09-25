# Project Settings
TARGET = game.exe
SRC_DIR = src
OBJ_DIR = obj

# Mencari file .c dan .cpp di folder src DAN subfolder tingkat 1
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*.cpp)

# Correctly map source paths and extensions to object directory
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter %.c, $(SOURCES))) \
          $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(filter %.cpp, $(SOURCES)))

# Compiler and Flags
TOOLCHAIN_PATH = D:/msys64/mingw64/bin
CC = $(TOOLCHAIN_PATH)/gcc
CXX = $(TOOLCHAIN_PATH)/g++
CFLAGS = -Wall -std=c99 -O2
CXXFLAGS = -Wall -std=c++17 -O2

# Raylib Paths
RAYLIB_PATH = C:/raylib/raylib
INCLUDE_PATHS = -Isrc -I$(RAYLIB_PATH)/src -Ilocal_include
LDFLAGS = -L$(RAYLIB_PATH)/src -Llib

# Windows Libraries required by Raylib
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm 

# Build Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

# PERBAIKAN: Menggunakan mkdir -p standar Bash/Unix karena terminalmu menggunakan /bin/sh
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -c $< -o $@

# PERBAIKAN: Menggunakan rm -rf standar Bash/Unix untuk membersihkan file
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
