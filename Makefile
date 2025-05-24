CC = gcc
LIB = src/glad.c -Llib -lglfw3dll
INCLUDE = -Iinclude

all: qge

qge:
	$(CC) qge.c $(LIB) $(INCLUDE) -o qge.exe