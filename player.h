#ifndef PLAYER_H
#define PLAYER_H

#include "tool.h"
#include "message.h"
#include "server.h"



t_player* accept_player();
void delete_player(t_player*);
void set_name(t_player*);
void notify_other_user_disconnected(t_game*);
int send_to_player(t_game*, t_player *,char *);
#endif
