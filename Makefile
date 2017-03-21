
CC	:= gcc

RM	:= rm -rf

LDFLAGS	+= -L.

CFLAGS	+= -Iinclude

SRCS	:= server.c

OBJS	:= $(SRCS:.c=.o)

NAME	:= server

TMP_FILE	:= *.*~ Makefile~

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(TMP_FILE)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
