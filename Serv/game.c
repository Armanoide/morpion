#include "game.h"

void* start_game(void* args) {

    t_player* player;

    player = (t_player*) args;
    set_name(player);
    prepare_next_game(player, NO);
    return NULL;
}

void prepare_next_game(t_player* player, int ask_new_game) {

    t_game* game = NULL;


    if (ask_new_game == YES) {
        switch (did_player_want_play_again(player)) {
            case YES: break;
            default:
            delete_player(player);
            return;
        }
    }

    game = get_available_game(player);
    if (game == NULL) {
        while (game == NULL) {
            game = create_game(player);
        }
    }
    clear_game(game);
    run_game(game, player);
}

int notify_if_can_begin(t_game* game){

    char buffer[255];


    if (game->player_1 != NULL && game->player_2 != NULL) {

        bzero(buffer, 255);
        strcpy(buffer, I_VERSUS);
        strcat(buffer, game->player_2->name);
        send_to_player(game, game->player_1, buffer);

        bzero(buffer, 255);
        strcpy(buffer, I_VERSUS);
        strcat(buffer, game->player_1->name);
        send_to_player(game, game->player_2, buffer);

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

int get_winner_game(t_game* game) {

    int indicator[SIZE_MAP*SIZE_MAP] = {8, 1, 6, 3, 5, 7, 4, 9, 2};
    int point_player_1 = 0;
    int point_player_2 = 0;
    int y = 0;
    int x;

    while (y < SIZE_MAP) {
        x = 0;
        while (x < SIZE_MAP) {
            if (game->map[y][x] == 1) {
                point_player_1 += indicator[y * 3 + x];
            }
            if (game->map[y][x] == 2) {
                point_player_2 += indicator[y * 3 + x];
            }
            x++;
        }
        y++;
    }

    if (point_player_1 == 15) {
        return 1;
    } else if (point_player_2 == 15) {
        return 2;
    } else if (point_player_1 + point_player_2 == 45) {
        return 0;
    } else {
        return -1;
    }
}

void terminate_game(t_game* game, t_player* player_1, t_player* player_2) {
    game->player_2 = NULL;
    game->player_1 = NULL;
    game->turn = NULL;
    prepare_next_game(player_1, YES);
    prepare_next_game(player_2, YES);
}

void present_player(t_game* game) {

}

void run_game(t_game* game, t_player* player) {

    int ret;
    t_req_game* req;
    fd_set readfds;
    int result_game;

    FD_ZERO(&readfds);
    FD_SET(player->socket, &readfds);
    game->count_hit = 0;

    if (notify_if_can_begin(game) == RET_ERROR) {
        return;
    }

    while(1) {

        ret = select(player->socket + 1, &readfds, NULL, NULL, NULL);
        if (ret > 0) {
            if (FD_ISSET(player->socket, &readfds)) {
                req = read_instruction(game, player);
                exec_instruction(req, game, player);
                result_game = get_winner_game(game);
                if (req != NULL) {
                    free(req);
                }
                if (result_game != -1) {
                    notify_game_over(game, result_game);
                    terminate_game(game, game->player_1, game->player_2);
                    return;
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
    read(player->socket, req->buffer, SIZE_BUFFER_READ);
    if (strlen(req->buffer) == 0) {
        printf("read error\n");
        req->type = ERROR_READ;
        return req;
    } else {
        if (strstr(req->buffer, I_COMMENT)){
            req->type = COMMENT;
        }
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
    return game;
}
