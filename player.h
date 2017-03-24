#ifndef PLAYER_H
#define PLAYER_H

#include "tool.h"
#include "message.h"
#include "server.h"



t_player* accept_player();
void delete_player(t_player* p);
void set_name(t_player* player);
#endif
