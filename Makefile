##
# @file
# @version 0.1

C_FLAGS = -Wall -Wextra -Werror -lm -lSDL2 -Iinclude
C_OUTPUT_FILE = sokoban

c: main.c src/*
	$(CC) main.c -o $(C_OUTPUT_FILE) src/* $(C_FLAGS)

clear:
	rm sokoban

run:
	./sokoban