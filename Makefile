CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
NAME		= minishell

INCS_DIR	= ./includes
INCS		= $(addprefix includes/, minishell.h)

LIBS		= librairies/libftfull_mac.a

SRCS		= parse/trim.c \
			parse/parsing.c \
			main.c

OBJS		= $(SRCS:.c=.o)

%.o			: %.c
			@$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS)
			@$(CC) $(CFLAGS) -I$(INCS_DIR) $(OBJS) $(LIBS) -o $(NAME)

clean:
			@$(RM) $(OBJS)

fclean		: clean
			@$(RM) $(NAME)

re			: fclean all

.PHONY		: all clean fclean re
