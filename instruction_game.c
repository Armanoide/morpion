#include "game.h"
#include <string.h>


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


void instruction_transmet_comment(t_req_game* req, t_game* game, t_player* player) {

    send_to_player(game, game->player_1 == player ? game->player_2 : game->player_1 , req->buffer);
}

void instruction_get_hit_count(t_req_game* req, t_game* game, t_player* player) {

    bzero(req->buffer, SIZE_BUFFER_READ);

    sprintf(req->buffer, "%s%d\n", MSG_RESPONSE, game->count_hit);
    send_to_player(game, game->turn, req->buffer);
}

void instruction_transmet_new_value(t_req_game* req, t_game* game, int y, int x) {

    bzero(req->buffer, SIZE_BUFFER_READ);
    sprintf(req->buffer, "%s%d,%d\n", I_NEW_VALUE, y, x);
    send_to_player(game, game->turn, req->buffer);
}

void instruction_get_value(t_req_game* req, t_game* game, t_player* player) {

    bzero(req->buffer, SIZE_BUFFER_READ);

    if (req->x >= 0 && req->x <= SIZE_MAP && req->y >= 0 && req->y <= SIZE_MAP) {
        sprintf(req->buffer, "%s%d\n", MSG_RESPONSE, game->map[req->y][req->x]);
        send_to_player(game, player, req->buffer);
    } else {
        send_to_player(game, player, MSG_BAD_CORD);
    }
}

void instruction_set_value(t_req_game* req, t_game* game, t_player* player) {

    if (req->x >= 0 && req->x <= SIZE_MAP && req->y >= 0 && req->y <= SIZE_MAP) {

        if (game->turn == player) {
            if (game->map[req->y][req->x] == 0) {
                game->map[req->y][req->x] = game->player_1 == player ? 1 : 2;
                game->turn = game->turn == game->player_1 ? game->player_2 : game->player_1;
                send_to_player(game, player, MSG_OK);
                instruction_transmet_new_value(req, game, req->y, req->x);
                send_to_player(game, game->turn, I_TURN);
                game->count_hit++;
            } else {
                send_to_player(game, player, MSG_BAD_SET);
            }
        } else {
            send_to_player(game, player, MSG_BAD_TURN);
        }

    } else {
        send_to_player(game, player, MSG_BAD_CORD);
    }
}

void instruction_display_map(t_req_game* req, t_game* game, t_player* player) {

    int x;
    int y;
    int i;

    i = 0;
    y = 0;
    bzero(req->buffer, SIZE_BUFFER_READ);
    while (y < SIZE_MAP) {
        x = 0;
        while (x < SIZE_MAP) {
            req->buffer[i] = game->map[y][x] + '0';
            x++;
            i++;
        }
        req->buffer[i] = '\n';
        i++;
        y++;
    }
    req->buffer[i] = '\0';
    send_to_player(game, player, req->buffer);
}
