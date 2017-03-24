#ifndef GAME_H
#define GAME_H

#include "tool.h"
#include "message.h"
#include "server.h"
#include <pthread.h>

#define SIZE_MAP 3

t_game* create_game();
t_game* get_available_game();
void* start_game(void*);
#endif
