
# Project Sokoban

Authors:
 * Nathael CARLIER
 * Sacha DAVID

The goal of this project is to recreate the game [Sokoban](https://fr.wikipedia.org/wiki/Sokoban) using the C programming language.

## Requirements

If you need to compile the code, please install the following C packages :
- SDL2, [help](https://wiki.libsdl.org/SDL2/Installation).
- SDL2_image, [help](https://www.oreilly.com/library/view/rust-programming-by/9781788390637/ac509577-fdbc-4f2e-b876-3536985e113c.xhtml).
- SDL_ttf

## Installation

``` bash
git clone https://gitlab.isima.fr/nacarlier/sokoban.git
```

## Execution

To compile and launch the game, please use the `make all` bash command.

Here are all the commands and their descriptions to compile different parts of the project.

| Command      | Description                          |
|:------------:|:------------------------------------:|
| `make c`     | Compile the program                  |
| `make run`   | Run the game                         |
| `make clean` | Remove the executable                |
| `make all`   | Compile and run the executable       |
| `make doc`   | Compile the `Doxygen` documentation  |


## Documentation

The [`Doxygen`](./doc/redirect.html) documentation can be found in the [`doc`], If it is not already there, run `make doc` to create it.

## Report

The project's [rapport](../../rapport/rapport.pdf) PDF can be found in the [`rapport`] folder.
