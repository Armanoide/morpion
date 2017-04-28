#ifndef PLAYER_H
#define PLAYER_H

#include "tool.h"
#include "message.h"
#include "server.h"


int did_player_want_play_again(t_player* player);
t_player* accept_player();
void delete_player(t_player*);
void set_name(t_player*);
void notify_other_user_disconnected(t_game*);
int send_to_player(t_game*, t_player *,char *);
void notify_game_over(t_game*, int);
#endif
