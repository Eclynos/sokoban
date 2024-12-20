#include "./include/includes.h"

int main() {

    createMap();
    App app = initApp();

    SDL_Surface* surface_perso = IMG_Load("./assets/test.png");
    if (!surface_perso) {
        printf("Error init image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(app.renderer);
        SDL_DestroyWindow(app.window);
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Texture* perso = SDL_CreateTextureFromSurface(app.renderer, surface_perso);
    SDL_FreeSurface(surface_perso); // Libérer la surface, la texture suffit maintenant
    if (!perso) {
        printf("Erreur lors de la création de la texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(app.renderer);
        SDL_DestroyWindow(app.window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface_bg = IMG_Load("./assets/background.png");
    SDL_Texture* bg = SDL_CreateTextureFromSurface(app.renderer, surface_bg);

    // Position initiale de l'image
    SDL_Rect imgRect = {100, 100, 50, 50}; // {x, y, largeur, hauteur}


    SDL_bool program_launched = SDL_TRUE;
    
    while (program_launched) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                program_launched = SDL_FALSE;
            } 
            else if (event.type == SDL_KEYDOWN) {
                // Gestion des touches
                switch (event.key.keysym.sym) {
                    case SDLK_z:
                        imgRect.y -= 100; // Déplacer vers le haut
                        break;
                    case SDLK_s:
                        imgRect.y += 100; // Déplacer vers le bas
                        break;
                    case SDLK_q:
                        imgRect.x -= 100; // Déplacer vers la gauche
                        break;
                    case SDLK_d:
                        imgRect.x += 100; // Déplacer vers la droite
                        break;
                }
            }
        }

        // Effacer l'écran
        SDL_RenderClear(app.renderer);
        
        // Afficher la texture
        SDL_RenderCopy(app.renderer, bg, NULL, NULL);
        SDL_RenderCopy(app.renderer, perso, NULL, &imgRect);

        // Mettre à jour l'écran
        SDL_RenderPresent(app.renderer);
    }

    SDL_DestroyTexture(perso);
    SDL_DestroyTexture(bg);
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

