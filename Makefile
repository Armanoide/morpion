
CC	:= gcc

RM	:= rm -rf

LDFLAGS	+= -L.

CFLAGS	+= -Iinclude

SRCS_SERVER	:= 	server.c \
				player.c \
				game.c \
				instruction_game.c

OBJS_SERVER	:= $(SRCS_SERVER:.c=.o)

NAME_SERVER	:= server

TMP_FILE	:= *.*~ Makefile~ 

all: $(NAME_SERVER)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) -o $(NAME_SERVER) $(OBJS_SERVER) $(LDFLAGS) -g -pthreads

clean:
	$(RM) $(OBJS_SERVER) $(TMP_FILE)

fclean: clean
	$(RM) $(NAME_SERVER)

re: fclean all

.PHONY: all re clean fclean
