#include "player.h"


int did_player_want_play_again(t_player* player) {

    char buffer[10];
    char* rep_test;
    unsigned long length;

    send_to_player(NULL, player, I_NEXT_GAME);
    while(1) {
        read(player->socket, buffer, 10);
        rep_test = strstr(buffer, MSG_RESPONSE);
        if (rep_test == NULL) {
            write(player->socket, MSG_KO, strlen(MSG_KO));
            continue;
        }
        length = strlen(buffer) - strlen( MSG_RESPONSE);
        rep_test = &buffer[strlen( MSG_RESPONSE)];
        if (rep_test != NULL && &rep_test[0] != NULL) {
            switch (rep_test[0]) {
                case 'y':
                write(player->socket, MSG_OK, strlen(MSG_OK));
                return YES;
                case 'Y':
                write(player->socket, MSG_OK, strlen(MSG_OK));
                return YES;
                default: return NO;
            }
        }
        break;
    }

    return RET_ERROR;
}

int send_to_player(t_game* game, t_player *player, char* buffer) {
    if (write(player->socket, buffer, strlen(buffer)) <= 0){
        notify_other_user_disconnected(game);
        return RET_ERROR;
    }
    return RET_SUCCESS;
}


void notify_game_over(t_game* game, int result_game) {

    if (result_game == 0) {
        send_to_player(game, game->player_1, I_EQUAL);
        send_to_player(game, game->player_2, I_EQUAL);

    } else {
        send_to_player(game, result_game == 1 ? game->player_1 : game->player_2, I_WINNER);
        send_to_player(game, result_game == 1 ? game->player_2 : game->player_1, I_LOOSER);
    }

}

void notify_other_user_disconnected(t_game* game) {
    if (game == NULL) {
        return;
    }
}


void set_name(t_player* player) {

    char buffer[250];
    unsigned long length;
    char* name_test;

    while(1) {
        read(player->socket, buffer, 250);
        name_test = strstr(buffer, I_NAME);
        if (name_test == NULL) {
            write(player->socket, MSG_KO, strlen(MSG_KO));
            continue;
        }
        length = strlen(buffer) - strlen(I_NAME);
        player->name = malloc(sizeof(char) * length + 1);
        strncpy(player->name, buffer + strlen(I_NAME), length);
        write(player->socket, MSG_OK, strlen(MSG_OK));
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
