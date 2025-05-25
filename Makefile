CC = gcc
SRC_FILES = src/glad.c
LIB = -Llib -lglfw3dll
INCLUDE = -Iinclude
FLAGS = -g -fdiagnostics-color=always -Wall

all: qge

qge:
	$(CC) qge.c $(SRC_FILES) $(LIB) $(INCLUDE) $(FLAGS) -o qge.exe