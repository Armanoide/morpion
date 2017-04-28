#ifndef TOOL_H
#define TOOL_H

#define RET_ERROR   1
#define RET_SUCCESS 0

#define YES 0
#define NO 1

#define SIZE_BUFFER_READ 4096


#include <pthread.h>


typedef enum request_type {
    COUNT_HIT = 0,
    ERROR_READ = 1,
    UNKNOWN = 2,
    GET_VALUE = 3,
    SET_VALUE = 4,
    DISPLAY_MAP = 5,
    COMMENT = 6,
    EXIT = 7,
    GIVE_UP = 8,
} t_request_type;

typedef struct request_game {
    int x;
    int y;
    t_request_type type;
    char buffer[SIZE_BUFFER_READ];

} t_req_game;

typedef struct game_morpion {
    int **map;
    int count_hit;
    struct player_morpion* player_1;
    struct player_morpion* player_2;
    struct player_morpion* turn;
    struct game_morpion *prev;
    struct game_morpion *next;
} t_game;

typedef struct player_morpion {
    char* name;
    int socket;
    t_game* game;
} t_player;

typedef struct server_morpion {
    int socket_server;
    t_game* games;
    pthread_mutex_t mutex;
} t_server;

t_server* get_server(void);

#endif
