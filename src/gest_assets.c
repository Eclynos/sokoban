#include "gest_assets.h"

/**
 * \file gest_assets.c
 * \brief Gestion des variables d'affichage.
**/

/**
 * \fn SDL_Texture* createEntity(const char * filename, Game * game)
 * 
 * \brief Création de texture.
 * 
 * \param filename Chemin relatif vers le fichier de l'image que l'on va transformer en texture.
 * \param game Srtucture Game nécessaire à l'affilation de la texture avec le rendu.
 * 
 * \return Texture interprétable par SDL2.
 */
SDL_Texture* createEntity(const char * filename, Game * game){

    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        printf("Error init surface: %s\n", IMG_GetError());
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    if (!texture) {
        printf("Erreur init texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(surface);
    return texture;
}

/**
 * \fn TTF_Font* createFont(const char * filename, Game * game)
 * 
 * \brief Création de police d'écriture.
 * 
 * \param filename Chemin relatif vers le fichier que l'on va transformer en police d'écriture.
 * \param game Srtucture Game a détruire si l'initialisation ce passe mal.
 * 
 * \return Police interprétable par SDL2.
 */
TTF_Font* createFont(const char * filename, Game * game) {

    TTF_Font* font = TTF_OpenFont(filename, TEXT_SIZE);
    if (!font) {
        printf("Erreur init police: %s\n", SDL_GetError());
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return font;
}

/**
 * \fn Text * createText(Game * game, TTF_Font * font, SDL_Color text_color, char * sentence, int x, int y, int w, int h)
 * 
 * \brief Création d'une structure de texte.
 * 
 * \param game Structure Game nécessaire à l'affilation du texte avec le rendu.
 * \param font Police d'écriture du texte.
 * \param text_color Couleur du texte.
 * \param sentence Phrase du texte
 * \param x, y Position du texte.
 * \param w, h Taille du texte.
 
 * \return Struct Texte initialiser.
 * \see Text
 */
Text * createText(Game * game, TTF_Font * font, SDL_Color text_color, char * sentence, int x, int y, int w, int h) {
    Text * text = (Text*)malloc(sizeof(*text));
    if (!text) {
        perror("Erreur allocation texte");
        exit(EXIT_FAILURE);
    }

    SDL_Surface * textSurface = TTF_RenderText_Solid(font, sentence, text_color);
    text->texture = SDL_CreateTextureFromSurface(game ->renderer, textSurface);
    text->rect = (SDL_Rect){x, y, w, h};
    text->sentence = sentence;
    SDL_QueryTexture(text->texture, NULL, NULL, &text->rect.w, &text->rect.h);
    SDL_FreeSurface(textSurface);

    return text;
}

/**
 * \fn updateText(Game * game, Text * text, TTF_Font * font, SDL_Color text_color, char * sentence)
 * 
 * \brief Mise à jour de la texture d'une structure texte avec son nouveau texte.
 * 
 * \param game Structure contenant les variables générales du jeu.
 * \param text La structure à modifier.
 * \param font Police d'écriture du texte.
 * \param text_color Couleur du texte.
 * \param sentence Phrase du texte (Elle est censée être différente de celle de la dernière fois).
 * 
 * \see text
 */
void updateText(Game * game, Text * text, TTF_Font * font, SDL_Color text_color, char * sentence) {
    SDL_Surface * textSurface = TTF_RenderText_Solid(font, sentence, text_color);
    text->texture = SDL_CreateTextureFromSurface(game ->renderer, textSurface);
    SDL_QueryTexture(text->texture, NULL, NULL, &text->rect.w, &text->rect.h);
    SDL_FreeSurface(textSurface);
}

/**
 * \fn void freeText(Text * text)
 * 
 * \brief Libère la place prie par la structure Text donnée.
 * 
 * \param text Struct à free.
 * 
 * \see Text
 */
void freeText(Text * text) {
    SDL_DestroyTexture(text->texture);
    free(text);
}

/**
 * \fn void showBackground(Game * game, Map * map, Background * background)
 * 
 * \brief Affiche le background du jeu.
 * 
 * \param game Structure contenant les variables générales du jeu.
 * \param map Structure de la carte contenant les informations de celle-ci.
 * \param background Structure de l'arrière plan contenant les nombreuses textures nécessaires à son affichage.
 * 
 * \see Background
 */
void showBackground(Game * game, Map * map, Background * background) {
    //srand(time(NULL));
    int i, j;
    SDL_Rect tileRect;
    int tile_size = map->tile_size;
    int rows = map->rows;
    int cols = map->cols;
    SDL_RenderCopy(game->renderer, background->water, NULL, NULL);

    // Affichage de la terre tout autour
    for (i = -rows * 2; i < rows * 4; ++i) {
        for (j = -cols; j < cols * 2; ++j) {
            tileRect = (SDL_Rect){(game->screensize.w/2) + (j * tile_size - i * tile_size) / 2,
                                    map->up_space + (j * tile_size + i * tile_size) / 4,
                                    tile_size, tile_size};
            if (i < 0 || j < -1 || i > rows || j > cols) {
                SDL_RenderCopy(game->renderer, background->ground, NULL, &tileRect);
            }
        }
    }

    // Affichage des bordures
    for (i = -1; i < cols; ++i) {
        tileRect = (SDL_Rect){(game->screensize.w/2) + (i * tile_size) / 2,
                                map->up_space + (i * tile_size) / 4,
                                tile_size, tile_size};
        if (game->frame == 0) {
            SDL_RenderCopy(game->renderer, background->submerged_borders[0], NULL, &tileRect);
        } else {
            SDL_RenderCopy(game->renderer, background->borders[0], NULL, &tileRect);
        }

        tileRect = (SDL_Rect){(game->screensize.w/2) + (-rows * tile_size + i * tile_size) / 2,
                                map->up_space + (rows * tile_size + i * tile_size) / 4,
                                tile_size, tile_size};
        if (game->frame == 0) {
            SDL_RenderCopy(game->renderer, background->submerged_borders[4], NULL, &tileRect);
        } else {
            SDL_RenderCopy(game->renderer, background->borders[4], NULL, &tileRect);
        }
    }

    for (i = 0; i < rows; ++i) {
        tileRect = (SDL_Rect){(game->screensize.w/2) + (cols * tile_size - i * tile_size) / 2,
                                map->up_space + (cols * tile_size + i * tile_size) / 4,
                                tile_size, tile_size};
        if (game->frame == 0) {
            SDL_RenderCopy(game->renderer, background->submerged_borders[2], NULL, &tileRect);
        } else {
            SDL_RenderCopy(game->renderer, background->borders[2], NULL, &tileRect);
        }
    }

    tileRect = (SDL_Rect){(game->screensize.w/2) + (-rows * tile_size + cols * tile_size) / 2,
                            map->up_space + (rows * tile_size + cols * tile_size) / 4,
                            tile_size, tile_size};
    if (game->frame == 0) {
        SDL_RenderCopy(game->renderer, background->submerged_borders[3], NULL, &tileRect);
    } else {
        SDL_RenderCopy(game->renderer, background->borders[3], NULL, &tileRect);
    }

    tileRect = (SDL_Rect){(game->screensize.w/2) + (cols * tile_size) / 2,
                            map->up_space + (cols * tile_size) / 4,
                            tile_size, tile_size};
    if (game->frame == 0) {
        SDL_RenderCopy(game->renderer, background->submerged_borders[1], NULL, &tileRect);
    } else {
        SDL_RenderCopy(game->renderer, background->borders[1], NULL, &tileRect);
    }

    // Affichage de la cascade et de la falaise

    for (j = 0; j < WATERFALL_SIZE; ++j) {
        for (i = -rows * 2; i < rows * 4; ++i) {
            tileRect = (SDL_Rect){(cols * tile_size - i * tile_size) / 2,
                                    map->up_space + (-j * tile_size + i * tile_size) / 4,
                                    tile_size, tile_size};
            SDL_RenderCopy(game->renderer, background->cliff, NULL, &tileRect);
        }
        tileRect = (SDL_Rect){(cols * tile_size - map->waterfall_position * tile_size) / 2,
                                map->up_space + (-j * tile_size + map->waterfall_position * tile_size) / 4,
                                tile_size, tile_size};
        if ((j + game->frame) % 2 == 0) {
            SDL_RenderCopy(game->renderer, background->waterfall[0], NULL, &tileRect);
        } else {
            SDL_RenderCopy(game->renderer, background->waterfall[1], NULL, &tileRect);
        }
    }

    for (i = 0; i < 2; ++i) {
        tileRect = (SDL_Rect){(cols * tile_size - map->waterfall_position * tile_size - i * tile_size + tile_size * 3/4) / 2,
                        map->up_space + (map->waterfall_position * tile_size + i * tile_size + tile_size * 3/4) / 4,
                        tile_size, tile_size};
        if ((i + game->frame) % 2 == 0) {
            SDL_RenderCopy(game->renderer, background->foam[0], NULL, &tileRect);
        } else {
            SDL_RenderCopy(game->renderer, background->foam[1], NULL, &tileRect);
        }
    }

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < 2; ++j) {
            tileRect = (SDL_Rect){(cols * tile_size - map->waterfall_position * tile_size - i * tile_size - tile_size + j * tile_size) / 2,
                                map->up_space + (map->waterfall_position * tile_size - i * tile_size - WATERFALL_SIZE * tile_size + tile_size/2 - j * tile_size - tile_size * 3/4) / 4,
                                tile_size, tile_size};
            if ((i + game->frame) % 2 == 0) {
                SDL_RenderCopy(game->renderer, background->moving_water[0], NULL, &tileRect);
            } else {
                SDL_RenderCopy(game->renderer, background->moving_water[1], NULL, &tileRect);
            }
        }
    }
}

/**
 * \fn void showAllEntities(Game * game, Map * map, Player * player, SDL_Texture* box, SDL_Texture* goal, SDL_Texture* rock, SDL_Texture* tex_void, SDL_Texture* goal_boxed, SDL_Texture* frog_rock, SDL_Texture* rock_submerged, SDL_Texture* frog_rock_submerged)
 * 
 * \brief Fait le rendue de toute les textures des éléments du jeu.
 * 
 * \param game Structure contenant les variables générales du jeu.
 * \param map Struct Map servant a placer au bon endroit les texture dans la fenêtre de jeu.
 * \param SDL_Texture Toutes les textures a afficher.
 */
void showAllEntities(Game * game, Map * map, Player * player, SDL_Texture* box, SDL_Texture* goal, SDL_Texture* rock, SDL_Texture* tex_void, SDL_Texture* goal_boxed, SDL_Texture* frog_rock, SDL_Texture* rock_submerged, SDL_Texture* frog_rock_submerged){
    int i, j;
    SDL_Rect tileRect;
    int tile_size = map->tile_size;

    for (i = 0; i < map->rows; ++i) {
        for (j = 0; j < map->cols; ++j) {
            tileRect = (SDL_Rect){(game->screensize.w/2) + (j * tile_size - i * tile_size) / 2,
                                    map->up_space + (j * tile_size + i * tile_size) / 4,
                                    tile_size, tile_size};
            switch (map->tab[i][j]) {
            case ' ': // trouver une formule math pour faire en sorte que de temps en temps il y ait une bulle
                if ((game->frame * i + j) % 16 == 0 && j != 0) {
                    SDL_RenderCopy(game->renderer, tex_void, NULL, &tileRect);
                }
                break;
            case 'W': // Wall
                if (game->frame == 0) {
                    SDL_RenderCopy(game->renderer, rock_submerged, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(game->renderer, rock, NULL, &tileRect);
                }
                break;
            case 'C': // Box
                if (game->frame == 0) --tileRect.y;
                if (map->initial_tab[i][j] == 'I') {
                    SDL_RenderCopy(game->renderer, goal_boxed, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(game->renderer, box, NULL, &tileRect);
                }
                break;
            case 'I': // Goal
                if (game->frame == 0) --tileRect.y;
                SDL_RenderCopy(game->renderer, goal, NULL, &tileRect);
                break;
            case 'P': // Player
                SDL_RenderCopy(game->renderer, player->texture[player->direction][game->frame], NULL, &tileRect);
                break;
            case 'F': // Other type of rocks
                if (game->frame == 0) {
                    SDL_RenderCopy(game->renderer, frog_rock_submerged, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(game->renderer, frog_rock, NULL, &tileRect);
                }
                break;
            default:
                break;
            }
        }
    }
}

/**
 * \fn void showInteractives(Game * game, TTF_Font * font, SDL_Color text_color, Text * start, Text * level, Text * moves, Text * text_level, Text * text_moves, int map_nb, int nb_moves)
 * 
 * \brief 
 * 
 * \param game Structure contenant les variables générales du jeu.
 * \param font Police d'écriture du texte.
 * \param text_color Couleur du texte.
 * \param Text* Toutes les structures texte a afficher.
 * \param map_nb Le numéro de la map actuellement affichée.
 * \param nb_moves Le nombre de mouvements effectués par le joueur.
 * 
 * \see Text
 */
void showInteractives(Game * game, TTF_Font * font, SDL_Color text_color, Text * start, Text * level, Text * moves, Text * text_level, Text * text_moves, int map_nb, int nb_moves) {

    if (map_nb == 0) {
        SDL_RenderCopy(game->renderer, start->texture, NULL, &start->rect);
    } else {
        if (atoi(level->sentence) != map_nb) {
            char newsentence[10];
            sprintf(newsentence, "%d", map_nb);
            updateText(game, level, font, text_color, newsentence);
        }
        SDL_RenderCopy(game->renderer, text_level->texture, NULL, &text_level->rect);
        SDL_RenderCopy(game->renderer, level->texture, NULL, &level->rect);
    }

    if (atoi(moves->sentence) != nb_moves) {
        char newsentence[10];
        sprintf(newsentence, "%d", nb_moves);
        updateText(game, moves, font, text_color, newsentence);
    }

    SDL_RenderCopy(game->renderer, text_moves->texture, NULL, &text_moves->rect);
    SDL_RenderCopy(game->renderer, moves->texture, NULL, &moves->rect);
}

/**
 * \fn void capFPS(Uint32 start_time)
 * 
 * \brief Limite les FPS à 60.
 * 
 * \param start_time Le tick de début de frame.
*/
void capFPS(Uint32 start_time) {
    Uint32 frameTime = SDL_GetTicks() - start_time;
    if (FRAME_DELAY > frameTime) {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

/**
 * \fn void frameAnimation(Game* game, Uint32* last_animation_time)
 * 
 * \brief Décide si il faut passer ou non à la frame d'animation suivante.
 * 
 * \param game Structure contenant les variables générales du jeu.
 * \param last_animation_time tick du dernier changement de frame, si sa différence est trop grande avec le tick actuel, on passe une frame.
 */
void frameAnimation(Game* game, Uint32* last_animation_time){
    Uint32 current_time = SDL_GetTicks();
    if (game->frame == 0) {
        if (current_time - *last_animation_time >= MS_BETWEEN_ANIMATIONS * 2) { // en ms
            ++game->frame;
            if (game->frame > NB_ANIMATIONS - 1) game->frame = 0;
            *last_animation_time = current_time;
        }
    } else {
        if (current_time - *last_animation_time >= MS_BETWEEN_ANIMATIONS) { // en ms
            ++game->frame;
            if (game->frame > NB_ANIMATIONS - 1) game->frame = 0;
            *last_animation_time = current_time;
        }
    }
}

/**
 * \fn Background * initBackgroundTextures(Game * game)
 * 
 * \brief Initialise les structures de l'arrière plan.
 * 
 * \param game Structure contenant les variables générales du jeu.
 * 
 * \return 
 * \see Background
 */
Background * initBackgroundTextures(Game * game) {
    unsigned int i;
    char filename[40];
    Background * background = (Background*)malloc(sizeof(*background));
    if (!background) {
        perror("Erreur allocation de la structure des textures d'arrière plan");
        exit(EXIT_FAILURE);
    }

    background->borders = malloc(5 * sizeof(SDL_Texture *));
    if (background->borders == NULL) {
        perror("Erreur allocation des textures des bordures");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 5; ++i) {
        sprintf(filename, "%s%d%s", BORDERS_PATH, i+1, ".png");
        background->borders[i] = createEntity(filename, game);
    }

    background->submerged_borders = malloc(5 * sizeof(SDL_Texture *));
    if (background->submerged_borders == NULL) {
        perror("Erreur allocation des textures des bordures submergées");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 5; ++i) {
        sprintf(filename, "%s%d%s", BORDERS_PATH, i+1, "_sub.png");
        background->submerged_borders[i] = createEntity(filename, game);
    }

    background->waterfall = malloc(2 * sizeof(SDL_Texture *));
    if (background->waterfall == NULL) {
        perror("Erreur allocation des textures de la cascade");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 2; ++i) {
        sprintf(filename, "%s%d%s", WATERFALL_PATH, i+1, ".png");
        background->waterfall[i] = createEntity(filename, game);
    }

    background->moving_water = malloc(2 * sizeof(SDL_Texture *));
    if (background->moving_water == NULL) {
        perror("Erreur allocation des textures de la cascade");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 2; ++i) {
        sprintf(filename, "%s%d%s", MOVING_WATER_PATH, i+1, ".png");
        background->moving_water[i] = createEntity(filename, game);
    }

    background->foam = malloc(2 * sizeof(SDL_Texture *));
    if (background->foam == NULL) {
        perror("Erreur allocation des textures de la cascade");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 2; ++i) {
        sprintf(filename, "%s%d%s", FOAM_PATH, i+1, ".png");
        background->foam[i] = createEntity(filename, game);
    }

    background->water = createEntity(WATER_IMAGE, game);
    background->ground = createEntity(GROUND_IMAGE, game);
    background->cliff = createEntity(CLIFF_IMAGE, game);

    return background;
}

/**
 * \fn void freeBackground(Background * background)
 * 
 * \brief Libére la place en mémoire prie par la structure background.
 * 
 * \param background Structure de l'arrière plan.
 * 
 * \see Background
 */
void freeBackground(Background * background) {
    int i;
    for (i = 0; i < 5; ++i) {
        SDL_DestroyTexture(background->borders[i]);
        SDL_DestroyTexture(background->submerged_borders[i]);
    }
    for (i = 0; i < 2; ++i) {
        SDL_DestroyTexture(background->waterfall[i]);
        SDL_DestroyTexture(background->moving_water[i]);
        SDL_DestroyTexture(background->foam[i]);
    }
    SDL_DestroyTexture(background->water);
    SDL_DestroyTexture(background->ground);
    SDL_DestroyTexture(background->cliff);
    free(background);
}
