#include "includes.h"

int main() {

    int i, j;
    SDL_Rect tileRect;
    App app = initApp();
    Map * map = createMap(FILE_MAP_1);

    SDL_Surface* surface_bg = IMG_Load(BACKGROUND_IMAGE);
    SDL_Surface* surface_perso = loadSurface(CHARACTER_IMAGE, app);
    SDL_Surface* surface_box = loadSurface(BOX_IMAGE, app);
    SDL_Surface* surface_goal = loadSurface(GOAL_IMAGE, app);
    SDL_Surface* surface_wall = loadSurface(WALL_IMAGE, app);
    SDL_Surface* surface_void = loadSurface(VOID_IMAGE, app);

    SDL_Texture* texture_bg = createTexture(surface_bg, app);
    SDL_Texture* texture_perso = createTexture(surface_perso, app);
    SDL_Texture* texture_box = createTexture(surface_box, app);
    SDL_Texture* texture_goal = createTexture(surface_goal, app);
    SDL_Texture* texture_wall = createTexture(surface_wall, app);
    SDL_Texture* texture_void = createTexture(surface_void, app);

    SDL_FreeSurface(surface_bg);
    SDL_FreeSurface(surface_perso);
    SDL_FreeSurface(surface_box);
    SDL_FreeSurface(surface_goal);
    SDL_FreeSurface(surface_wall);
    SDL_FreeSurface(surface_void);

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
                        imgRect.y -= 10; // Déplacer vers le haut
                        break;
                    case SDLK_s:
                        imgRect.y += 10; // Déplacer vers le bas
                        break;
                    case SDLK_q:
                        imgRect.x -= 10; // Déplacer vers la gauche
                        break;
                    case SDLK_d:
                        imgRect.x += 10; // Déplacer vers la droite
                        break;
                }
            }
        }

        SDL_RenderClear(app.renderer);
        
        SDL_RenderCopy(app.renderer, texture_bg, NULL, NULL);
        

        for (i = 0; i < map->rows; ++i) {
            for (j = 0; j < map->cols; ++j) {
                tileRect = (SDL_Rect){j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                switch (map->tab[i][j]) {
                case '#':
                    SDL_RenderCopy(app.renderer, texture_void, NULL, &tileRect);
                    break;
                case 'T':
                    SDL_RenderCopy(app.renderer, texture_wall, NULL, &tileRect);
                    break;
                case 'R':
                    SDL_RenderCopy(app.renderer, texture_box, NULL, &tileRect);
                    break;
                case '0': // on pourra ajouter un cas pour le goal recouvert par une caisse
                    SDL_RenderCopy(app.renderer, texture_goal, NULL, &tileRect);
                    break;
                case '1':
                    SDL_RenderCopy(app.renderer, texture_perso, NULL, &imgRect);
                default:
                    break;
                }
            }
        }

        SDL_RenderPresent(app.renderer);
    }

    freeMap(map);
    SDL_DestroyTexture(texture_bg);
    SDL_DestroyTexture(texture_perso);
    SDL_DestroyTexture(texture_box);
    SDL_DestroyTexture(texture_goal);
    SDL_DestroyTexture(texture_wall);
    SDL_DestroyTexture(texture_void);
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
