#ifndef SERVER_H
#define SERVER_H

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include "game.h"
#include "player.h"

void close_server(void);

#endif
