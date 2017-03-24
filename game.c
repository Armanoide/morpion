#include "game.h"

void* start_game(void* args) {

  t_player* player;
  t_game* game;

  player = (t_player*) args;

  set_name(player);
  game = get_available_game(player);
  if (game == NULL) {
    while (game == NULL) {
      game = create_game();
    }
  }

  while(1) {
    printf("%s\n", player->name);
    sleep(1);
  }
  return NULL;
}

t_game* get_available_game(t_player* player) {

  t_game* game;
  t_server *s;
  s = get_server();
  
  while(game != NULL) {
    if (game->player_1 == NULL) {
      game->player_1 = player;
      return game;
    }
    if (game->player_2 == NULL) {
      game->player_2 = player;
      return game;
    }
  }
  
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

