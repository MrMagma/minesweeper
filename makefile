SRC_DIR := src
OBJ_DIR := obj

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp, obj/%.o, $(SRC_FILES))

CC := g++
CFLAGS = -Wall -m64

all: minesweeper.exe

minesweeper.exe: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^
	
obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
