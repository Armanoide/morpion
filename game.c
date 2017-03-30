#include "game.h"

void* start_game(void* args) {
  
  t_player* player;
  t_game* game;
  
  player = (t_player*) args;

  //pthread_mutex_lock (&get_server()->mutex);
  set_name(player);
  game = get_available_game(player);
  if (game == NULL) {
    while (game == NULL) {
      game = create_game(player);
    }
  }
  //pthread_mutex_unlock(&get_server()->mutex);
  run_game(game, player);
  return NULL;
}

int notify_if_can_begin(t_game* game){
  
  if (game->player_1 != NULL && game->player_2 != NULL) {
    game->turn = game->player_1;
    return send_to_player(game, game->turn, I_TURN);
  }
  return 2;
}


void clear_game(t_game* game) {
    int y;
    int x;

    y = 0;
    while (y < SIZE_MAP) {
        x = 0;
        while (x < SIZE_MAP) {
            game->map[y][x] = 0;
            x++;
        }
        y++;
    }
}

void exec_instruction(t_req_game* req, t_game* game, t_player* player) {
    switch (req->type)
    {
        case ERROR_READ : notify_other_user_disconnected(game)                  ; break;
        case COMMENT    : instruction_transmet_comment(req, game, player)       ; break;
        case EXIT       : /*send_to_player(game, player, MSG_KO_CMD) */         ; break;
        case GIVE_UP    : /*send_to_player(game, player, MSG_KO_CMD) */         ; break;
        case UNKNOWN    : send_to_player(game, player, MSG_KO_CMD)              ; break;
        case SET_VALUE  : instruction_set_value(req, game, player)              ; break;
        case GET_VALUE  : instruction_get_value(req, game, player)              ; break;
        case DISPLAY_MAP: instruction_display_map(req, game, player)            ; break;
        case COUNT_HIT  : instruction_get_hit_count(req, game, player)          ; break;
    }
}

void run_game(t_game* game, t_player* player) {

  int ret;
  t_req_game* req;
  fd_set readfds;

  FD_ZERO(&readfds);
  FD_SET(player->socket, &readfds);

  if (notify_if_can_begin(game) == RET_ERROR) {
    return;
  }

    while(1) {
      ret = select(player->socket + 1, &readfds, NULL, NULL, NULL);
      if (ret > 0) {
        if (FD_ISSET(player->socket, &readfds)) {
          req = read_instruction(game, player);
            exec_instruction(req, game, player);
            if (req != NULL) {
              free(req);
            }
        }
      } else {
        printf("error durring select\n");
      }
    }
}


void get_coordinatate(t_req_game* req){

  int i;
  
  i = 0;
  
  while (req->buffer[i] != '\0' && req->buffer[i] != ':') {
    i++;
  }
  i++;
  
  req->y = atoi(&req->buffer[i]);
  
  while (req->buffer[i] != '\0' && req->buffer[i] != ',') {
    i++;
  }
  i++;
    
  req->x = atoi(&req->buffer[i]);
  
}

t_req_game* read_instruction(t_game* game, t_player* player) {
  
  t_req_game* req;
  
    req = malloc(sizeof(t_req_game));
    req->type = UNKNOWN;
    
    bzero(req->buffer, SIZE_BUFFER_READ);
    if (read(player->socket, req->buffer, SIZE_BUFFER_READ) <= 0) {
      printf("read error\n");
      req->type = ERROR_READ;
      return req;
    } else {
      if (strstr(req->buffer, I_SET_VALUE)){
        req->type = SET_VALUE;
        get_coordinatate(req);
      }
      if (strstr(req->buffer, I_GET_VALUE)){
        req->type = GET_VALUE;
        get_coordinatate(req);
      }
      if (strstr(req->buffer, I_DISPLAY)) {
        req->type = DISPLAY_MAP;
      }

      //instruction_set_coordinate();
      //if (game->player_1 != NULL && game->player_1 == player) {
      //  write(game->player_2->socket, buffer, strlen(buffer));
      //}
      //if (game->player_2 != NULL && game->player_2 == player) {
      //  write(game->player_1->socket, buffer, strlen(buffer));
      //}
      //printf("%s\n", buffer);
    }
    return req;
}

t_game* get_available_game(t_player* player) {
  
    t_game* game;
    t_server *s;
    
    s = get_server();
    game = s->games;
    while(game != NULL) {
      if (game->player_1 == NULL) {
        game->player_1 = player;
        return game;
      }
      if (game->player_2 == NULL) {
        game->player_2 = player;
        return game;
      }
      game = game->next;
    }
    return NULL;
}

void add_game_to_list(t_game* game) {
  t_server* server;
  t_game* tmp;
  
  server = get_server();
  tmp = server->games;
  if (tmp == NULL) {
    server->games = game;
  } else {
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = game;
  }
}


t_game* create_game(t_player *player) {

  t_game *game;
   int y;
  
  game = (t_game*) malloc(sizeof(t_game));
  game->next = NULL;
  game->prev = NULL;
  game->count_hit = 0;
  
  if (game == NULL) {
    return NULL;
  }
  
  game->map = malloc(sizeof(int**) * SIZE_MAP);
  y = 0;
  while (y < SIZE_MAP) {
    game->map[y] = (int*) malloc(sizeof(int) * SIZE_MAP);
    y++;
  }

  game->player_1 = player;
  game->player_2 = NULL;
  add_game_to_list(game);
  clear_game(game);
  return game;
}
