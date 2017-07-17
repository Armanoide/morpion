
CC	:= gcc

RM	:= rm -rf

LDFLAGS	+= -L.

CFLAGS	+= -I./Headers

SRCS_SERVER	:= 	./Serv/server.c \
				./Serv/player.c \
				./Serv/game.c \
				./Serv/instruction_game.c

SRCS_CLIENT	:= 	./Cli/client.c \
				./Cli/display.c


OBJS_SERVER	:= $(SRCS_SERVER:.c=.o) 

OBJS_CLIENT := $(SRCS_CLIENT:.c=.o)

NAME_SERVER	:= server

NAME_CLIENT := client

TMP_FILE	:= *.*~ Makefile~ 

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) -o $(NAME_SERVER) $(OBJS_SERVER) $(LDFLAGS) -g -pthreads

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(LDFLAGS) -lncurses

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(TMP_FILE)

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all re clean fclean
