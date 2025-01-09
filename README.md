
# Project Sokoban

Authors:
 * Nathael CARLIER
 * Sacha DAVID

Le but de ce projet est de recréer le jeu [Sokoban](https://fr.wikipedia.org/wiki/Sokoban) en utilisant le language de programmation C.

## Prérequis

Ces installations utiles uniquement si vous voulez compiler le code, pas besoin d'elles si vous voulez seulement executer le programme.
- SDL2, [help](https://wiki.libsdl.org/SDL2/Installation).
- SDL2_image, [help](https://www.oreilly.com/library/view/rust-programming-by/9781788390637/ac509577-fdbc-4f2e-b876-3536985e113c.xhtml).
- SDL_ttf

## Installation

Pour avoir le project, il suffit d'installer le fichier `.zip` ou d'utiliser git via cette commande:
``` bash
git clone https://gitlab.isima.fr/nacarlier/sokoban.git
```

## Exécution

Pour lancer le programme, utilisez la commande bash `make all` pour compiler et éxécuter le programme.

Voici toutes les commandes et leurs description pour compiler différentes parties du project.

| Commande     | Description                            |
|:------------:|:--------------------------------------:|
| `make c`     | Compile le programme                   |
| `make run`   | Exécute le jeu
| `make clean` | Supprime l'éxécutable                  |
| `make all`   | Compile et éxécute l'éxécutable        |
| `make doc`   | Compile la documentation `Doxygen`     |


## Documentation

La documentation [`Doxygen`](./doc/redirect.html) peut être trouvé dans le dossier [`doc`](./doc/), mais avant elle doit être crée via la commande bash associé `make doc`.

## Rapport

Le [rapport](./rapport/rapport.pdf) pdf du projet peut être trouvé dans le dosssier [`rapport`](./rapport/).