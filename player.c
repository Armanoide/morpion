#include "player.h"

int send_to_player(t_game* game, t_player *player, char* buffer) {
  if (write(player->socket, buffer, strlen(buffer)) <= 0){
    notify_other_user_disconnected(game);
    return RET_ERROR;
  }
  return RET_SUCCESS;
}

void notify_other_user_disconnected(t_game* game) {
  
}


void set_name(t_player* player) {

  char buffer[250];
  unsigned long length;
  char* name_test;
  
  while(1) {
    read(player->socket, buffer, 250);
    name_test = strstr(buffer, I_NAME);
    if (name_test == NULL) {
      write(player->socket, MSG_KO, 6);
      continue;
    }
    length = strlen(buffer) - 4;
    player->name = malloc(sizeof(char) * length + 1);
    strncpy(player->name, buffer + 4, length);
    write(player->socket, MSG_OK, 6);
    break;
  }
}



void delete_player(t_player* p) {

  if (p->socket) {
    write(p->socket, I_DISCONNECTED, strlen(I_DISCONNECTED));
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
      printf("accept failed\n");
      return NULL;
    }
  player = (t_player*) malloc(sizeof(t_player*));
  player->socket = client_fd;
  return player;
}
