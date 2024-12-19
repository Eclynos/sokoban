CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lm -lSDL2 -lSDL2_image
SRC = main.c src/fct_init.c
OUTPUT_FILE = sokoban

c:
	gcc $(CFLAGS) $(SRC) -o $(OUTPUT_FILE) $(LDFLAGS)


clean:
	rm -f $(OUTPUT_FILE)

run:
	./$(OUTPUT_FILE)