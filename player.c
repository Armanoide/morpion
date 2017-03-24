#include "player.h"

void delete_player(t_player* p) {

  if (p->socket) {
    write(p->socket, DISCONNECTED_MSG, 16);
    close(p->socket);
  }
}

t_player* accept_player() {

  t_server* s;
  struct sockaddr_in client_addr;
  int client_fd;
  t_player *player;
  int c;

  s = get_server();
  c = sizeof(struct sockaddr_in);
  client_fd = accept(s->socket_server, (struct sockaddr *)&client_addr, (socklen_t*)&c);
  if (client_fd < 0)
    {
      printf("accept failed");
      return NULL;
    }
  player = (t_player*) malloc(sizeof(t_player*));
  player->socket = client_fd;
  return player;
}
