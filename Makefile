CC = gcc
SRC_FILES = src/glad.c
LIB = -Llib -lglfw3dll
INCLUDE = -Iinclude

all: qge

qge:
	$(CC) qge.c $(SRC_FILES) $(LIB) $(INCLUDE) -o qge.exe