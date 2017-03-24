#include "game.h"

t_game* get_available_game() {

  return NULL;
}


t_game* create_game() {

  t_game *game;
  int i;

  i = 0;
  game = (t_game*) malloc(sizeof(t_game*));

  if (game == NULL) {
    return NULL;
  }
  
  game->map = malloc(sizeof(char**) * SIZE_MAP);  

  while(i < SIZE_MAP) {
    game->map[i] = (char*) malloc(sizeof(char) * SIZE_MAP);
    i++;
  }

  return game;
}

