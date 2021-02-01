CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
NAME		= minishell

INCS_DIR	= ./includes
INCS		= $(addprefix includes/, minishell.h)

LIBS		= librairies/libftfull.a

SRCS		= trim.c \
			parsing.c \
			prompt.c

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
