//http://broux.developpez.com/articles/c/sockets/
//http://www.binarytides.com/socket-programming-c-linux-tutorial/

#include "server.h"

void close_server() {
  t_server* server;

  server = get_server();
  if (server != NULL && server->socket_server != -1) {
    close(server->socket_server);
  }
}


t_server* get_server() {
  static t_server* server = NULL;

  if (server == NULL) {
    server = (t_server*) malloc(sizeof(t_server*));
  }
  return server;
}

void kill_server(int s) {

  close_server();
  printf("server close\n");
  exit(0);
}


int init_server(t_server *s) {

  struct sockaddr_in serv_addr;
  
  s->socket_server = socket(AF_INET, SOCK_STREAM, 0);
  if (s->socket_server == -1)
    {
      printf("Could not create socket");
      return 1;
    }

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(7777);
  if (bind(s->socket_server, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
      printf("bind fail");
      return 1;
    }

  listen(s->socket_server, 3);
  signal(SIGINT, kill_server);
  
  return 0;
}

int main() {

  t_player* player;
  t_game* game;

  if (init_server(get_server()) == 0) {
    while(1) {
      player = accept_player(get_server());
      if (player != NULL){
        continue;
      }
      int pid = fork();
      if (pid == 0) {

        get_available_game();
        
      } else if (pid < 0) {
        delete_player(player);        
      } else {

      }      
      game = create_game();
    }
  }
  
  return EXIT_SUCCESS;
}

