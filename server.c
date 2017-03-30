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
    server = (t_server*) malloc(sizeof(t_server));
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
      printf("Could not create socket\n");
      return 1;
    }

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(7777);
  if (bind(s->socket_server, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
      printf("bind fail\n");
      return 1;
    }

  listen(s->socket_server, 3);
  signal(SIGINT, kill_server);
  
  return 0;
}

int main() {

    t_server* server;
  t_player* player;
//  t_game* game;
//  int pid;

    server = get_server();
    server->games = NULL;
  if (init_server(server) == 0) {
    while(1) {
      player = accept_player(server);
      if (player == NULL){
        printf("client fail to connect\n");
        continue;
      }
      //      int pid = fork();
      //      if (pid == 0) {
        printf("client connected\n");
        pthread_t thread_player;
        pthread_create (&thread_player, NULL, start_game, player);
        //        pthread_join (thread_player, NULL);
        //      } else if (pid > 0) {
        //      } else {
        //        delete_player(player);
        //      }
    }
  }
  
  return EXIT_SUCCESS;
}
