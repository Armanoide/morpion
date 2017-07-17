#ifndef CLIENT_H
#define CLIENT_H


#include <sys/socket.h>
#include <arpa/inet.h>

#include "display.h"

typedef struct client_morpion {
  int socket_client;
  t_wrap* map;
  WINDOW* win_init;
  int position_cursor;
  int position_sent;
  int my_turn;
  int req_x;
  int req_y;
  int game_over;
  int win;
}t_client;

t_client* get_client(void);

#endif
