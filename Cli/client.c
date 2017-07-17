#include "client.h"
#include "message.h"


void parse_coordinate(t_client* client, char* buffer){

  int i;
  
  i = 0;

  while (buffer[i] != '\0' && buffer[i] != ':') {
    i++;
  }
  i++;

  client->req_y = atoi(&buffer[i]);

  while (buffer[i] != '\0' && buffer[i] != ',') {
    i++;
  }
  i++;

  client->req_x = atoi(&buffer[i]);

}

int m_getch()
{
  int r;
  unsigned char c;
  if ((r = read(0, &c, sizeof(c))) < 0) {
    return r;
  } else {
    return c;
  }
}

void close_client() {
  t_client* client;

  client = get_client();
  if (client != NULL && client->socket_client != -1) {
    close(client->socket_client);
  }
  if (client->win_init != NULL){
    endwin();
  }
  if (client->map != NULL) {
    for (int i = 0 ; i < 9; i++) {
      t_box* box = client->map->boxes[i];
      delwin(box->win);
      free(client->map->boxes[i]);
    }
    free(client->map->boxes);
    free(client->map);
  }
}

void kill_client(int s) {

  close_client();
  printf("client close\n");
  exit(0);
}

t_client* get_client() {

  static t_client* client = NULL;

  if (client == NULL) {
    client = (t_client*) malloc(sizeof(t_client));
    client->position_cursor = 0;
  }
  return client;
}

int init_client() {

  struct sockaddr_in client_addr;
  t_client* c; 
  
  c = get_client();
  c->socket_client = socket(AF_INET, SOCK_STREAM, 0);
  if (c->socket_client == -1)
    {
      return 1;
    }
 
  bzero(&client_addr, sizeof(client_addr));
  client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(7777);

  display_message_at_center(CONNECTION_TO_SERVER, 1);
  if (connect(c->socket_client, (struct sockaddr *)&client_addr,
              sizeof(client_addr)) < 0)
    {
      return 2;
    }
  signal(SIGINT, kill_client);
  return 0;
}

int register_username(t_client* client) {

  int row, col, r;
  char ch;
  char buffer[100];

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  clear();
  getmaxyx(stdscr, row, col);
  mvprintw(row/2, (col - strlen(ASK_USERNAME))/2, "%s", ASK_USERNAME);
  move(row/2 + 1, (col - strlen(ASK_USERNAME))/2);
  refresh();

  bzero(&buffer, 100);
  strcpy(buffer, I_NAME);
  while ( ch != '\n' )
    {
      ch = getch();
      strncat(buffer , &ch, 1);
    }

  write(client->socket_client, buffer, strlen(buffer));
  bzero(buffer, 100);
  r = read(client->socket_client, buffer, 100);
  if (r == 0) {
    return 1;
  } else if (strcmp(buffer, MSG_OK) == 0) {
    return 0;
  } else {
    return register_username(client);
  }
}

int reverse_get_coordinate(t_client* client){

  if (client->req_x == 0 && client->req_y == 0)
    return 0;
  if (client->req_x == 1 && client->req_y == 0)
    return 1;
  if (client->req_x == 2 && client->req_y == 0)
    return 2;
  if (client->req_x == 0 && client->req_y == 1)
    return 3;
  if (client->req_x == 1 && client->req_y == 1)
    return 4;
  if (client->req_x == 2 && client->req_y == 1)
    return 5;
  if (client->req_x == 0 && client->req_y == 2)
    return 6;
  if (client->req_x == 1 && client->req_y == 2)
    return 7;
  if (client->req_x == 2 && client->req_y == 2)
    return 8;  
  
  return -1;
}

int read_instruction(t_client* client) {
  char buffer[4096];
  int p;
  
  bzero(buffer, 4096);
  if (read(client->socket_client, buffer, 4096) == -1) {
    return 1;
  }

  //debug
  // endwin();
  // printf("[%s]\n", buffer);
  if (strstr(buffer, I_TURN) != NULL) {
    client->my_turn = 1;
  }

  if (client->my_turn == 1 && strstr(buffer, "//r:ok") != NULL)
    {
      client->my_turn = 0;
      client->map->boxes[client->position_sent]->is_a_cross = 1;
      clear();
    }

  if (strstr(buffer, "//nv") != NULL) {
    parse_coordinate(client, buffer);
    p = reverse_get_coordinate(client);
    if (p != -1) {
      client->map->boxes[p]->is_a_circle = 1;
    }   
  }

  if (strstr(buffer, "//over:you_win") != NULL) {
    client->game_over = 1;
    client->win = 1;
  }

  if (strstr(buffer, "//over:you_lose") != NULL) {
    client->game_over = 1;
    client->win = 0;
  }
 
  refresh();
  return 0;
}
  
char* get_coordinate(int position) {
  switch (position)
    {
    case 0: return "//s:0,0";
    case 1: return "//s:0,1";
    case 2: return "//s:0,2";
    case 3: return "//s:1,0";
    case 4: return "//s:1,1";
    case 5: return "//s:1,2";
    case 6: return "//s:2,0";
    case 7: return "//s:2,1";
    case 8: return "//s:2,2";
    }
  return "";
}

void run_client_game(t_client* client) {

  fd_set readfds;  
  int ret, a = 0;
  int row, col;
  char* bf;
  
  getmaxyx(stdscr, row, col); 
  while(a != 27) {

    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(client->socket_client, &readfds);
    print_map(client->map, client->position_cursor);
    ret = select(client->socket_client + 1, &readfds, NULL, NULL, NULL);

    if (ret > 0) {
      if (FD_ISSET(0, &readfds)) {
        a = getch();    
      }
      if (FD_ISSET(client->socket_client, &readfds)) {
        read_instruction(client);
      }
    }

    if (a == 113) {
      client->position_cursor--;
      client->position_cursor = client->position_cursor < 0
              ? 0 : client->position_cursor;
    }
    if (a == 100) {
      client->position_cursor++;
      client->position_cursor = client->position_cursor >= 9
        ? 8 : client->position_cursor;
    }
    if (a == 32 && client->my_turn == 1) {
      client->position_sent = client->position_cursor;
      bf = get_coordinate(client->position_cursor);
      write(client->socket_client, bf, strlen(bf));
      a = 0;
    }

    if (client->my_turn == 1) {
      mvprintw(1, (col - strlen("Your turn"))/2, "%s", "Your turn");  
    }

    if (client->game_over == 1) {
      if (client->win == 1) {
        mvprintw(1, (col - strlen("Your turn"))/2, "%s", "Your win");  
      } else {
        mvprintw(1, (col - strlen("Your turn"))/2, "%s", "Your loose");  
      }
    }
  }
  getch();
}


int main() {

  t_client* client;

  client = get_client();
  client->win_init =initscr();

    
  refresh();
  start_color();
  if (has_colors() == FALSE)
    {
      printf("Your terminal does not support color\n");
      close_client();
      return 1;
    }
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);
  attron(COLOR_PAIR(1));  

  print_logo();

  if ((client->map = create_map()) && client->map == NULL) {
    close_client();
    return 1;
  }

  
  if (init_client() != 0) {
    display_message_at_center(ERR_CONNECTION_FAIL, 1);
    getch();
    close_client();
    return 1;
  }

  if (register_username(client) != 0) {
    return 1;
  }


  init_box(client->map);

  noecho();
  nodelay(stdscr, TRUE);
  raw();

  run_client_game(client);
  close_client();
  return 0;
}

