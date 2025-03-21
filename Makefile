CFLAGS = -Wall -Iinclude -I/usr/include/SDL2
LDFLAGS = -lm -lSDL2 -lSDL2_image -lSDL2_ttf
SRC = main.c src/*
OUTPUT_FILE = sokoban.out

c:
	gcc $(CFLAGS) $(SRC) -o $(OUTPUT_FILE) $(LDFLAGS)

run:
	./$(OUTPUT_FILE)
	
clean:
	rm -f $(OUTPUT_FILE)


all:
	gcc $(CFLAGS) $(SRC) -o $(OUTPUT_FILE) $(LDFLAGS)
	./$(OUTPUT_FILE)

doc:
	doxygen doc/Doxyfile