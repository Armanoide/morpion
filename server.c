#include <strings.h>
#include <stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>

typedef struct server_morpion {
  int socket_server;
  
}t_serv;

int init_server(t_serv *s) {

  struct sockaddr_in serv_addr;
  
  s->socket_server = socket(AF_INET, SOCK_STREAM , 0);
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
  return 0;
}



int main() {

  t_serv s;
  int client_fd;
  struct sockaddr_in client_addr;

  int c = sizeof(struct sockaddr_in);
  if (init_server(&s) == 0) {
    client_fd = accept(s.socket_server, (struct sockaddr *)&client_addr, (socklen_t*)&c);
    if (client_fd < 0)
      {
        printf("accept failed");
      }
  }

  write(client_fd, "coucou", 6);
  close(s.socket_server);
  return EXIT_SUCCESS;
}
