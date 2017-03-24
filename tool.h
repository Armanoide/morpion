#ifndef TOOL_H
#define TOOL_H


typedef struct game_morpion {
  char **map;
}t_game;

typedef struct player_morpion {
  int socket;
  t_game* game;
}t_player;

typedef struct server_morpion {
  int socket_server;
  
}t_server;

t_server* get_server(void);

#endif
