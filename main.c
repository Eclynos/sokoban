#include <SDL2/SDL.h>
#include <stdio.h>
#include "constants.h"
#include "fct_utile.h"

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      printf("Erreur lors de l'initialisation de la SDL: %s\n", SDL_GetError());
      return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
      "Sokoban",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      800,
      600,
      SDL_WINDOW_SHOWN
  );

  if (!window) {
      printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
      SDL_Quit();
      return 1;
  }

  SDL_Event event;
  int running = 1;
  while (running) {
      while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
              running = 0;
          }
      }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}