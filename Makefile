SRC_DIR := src
OBJ_DIR := obj

TARGET := minesweeper.exe

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp, obj/%.o, $(SRC_FILES))

CC := g++
CFLAGS = -Wall -m64

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^
	
obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
