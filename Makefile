##
# @file
# @version 0.1

C_FLAGS = -Wall -Wextra -Werror -lm
C_OUTPUT_FILE = main.out

c: main.c src/*
	$(CC) main.c -o $(C_OUTPUT_FILE) src/* $(C_FLAGS)

clear:
	rm main.out

run:
	./main.out

#end
