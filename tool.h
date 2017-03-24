#ifndef TOOL_H
#define TOOL_H


typedef struct game_morpion {
  char **map;
  struct player_morpion* player_1;
  struct player_morpion* player_2;
  struct game_morpion *prev;
  struct game_morpion *next;
}t_game;

typedef struct player_morpion {
  char* name;
  int socket;
  t_game* game;
}t_player;

typedef struct server_morpion {
  int socket_server;
  
}t_server;

t_server* get_server(void);

#endif
