#ifndef GAME_H
#define GAME_H

#include "tool.h"
#include "message.h"
#include "server.h"
#include <pthread.h>

#define SIZE_MAP 3

void instruction_transmet_comment(t_req_game* req, t_game* game, t_player* player);
void instruction_get_value(t_req_game* req, t_game* game, t_player* player);
void instruction_transmet_new_value(t_req_game* req, t_game* game, int y, int x);
void instruction_get_hit_count(t_req_game* req, t_game* game, t_player* player);
void instruction_display_map(t_req_game* req, t_game* game, t_player* player);
void instruction_set_value(t_req_game* req, t_game* game, t_player* player);
t_req_game* read_instruction(t_game*, t_player*);
void run_game(t_game*, t_player*);
t_game* create_game(t_player*);
t_game* get_available_game(t_player*);
void* start_game(void*);
#endif
