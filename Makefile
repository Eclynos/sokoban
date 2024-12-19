##
# @file
# @version 0.1

C_FLAGS = -Wall -Wextra -Werror -lm -lSDL2 -lSDL2_image -Iinclude
C_OUTPUT_FILE = sokoban.out

c: main.c src/*
	$(CC) main.c -o $(C_OUTPUT_FILE) src/* $(C_FLAGS)

clear:
	rm $(C_OUTPUT_FILE) 

run:
	./$(C_OUTPUT_FILE) 
