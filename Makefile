CC			= clang -Wall -Wextra -Werror
RM			= rm -rf
NORME		= norminette
NAME		= minishell 
INCS_DIR	= ./includes/
MAIN_INC	= -I$(INCS_DIR)

LIB_DIR		= ./libft/
LIB_INC		= -I$(LIB_DIR)includes/
LIB_NAME	= $(LIB_DIR)libft.a

INCS		= $(addprefix $(INCS_DIR), minishell.h)

SRCS		=  $(addprefix sources/, \
			execute/types.c \
			execute/fork.c \
			execute/command.c \
			execute/execute.c \
			execute/executable.c \
			execute/useful.c \
			execute/useful2.c \
			parse/count.c \
			parse/env.c \
			parse/parse.c \
			parse/redir.c \
			parse/state.c \
			parse/tree.c \
			parse/useful.c \
			reader/reader.c \
			utilities/errors.c \
			utilities/print.c \
			utilities/free.c \
			builtin/cd.c \
			builtin/echo.c \
			builtin/env.c \
			builtin/exit.c \
			builtin/export.c \
			builtin/export_sorted.c \
			builtin/pwd.c \
			builtin/unset.c \
			expand/useful.c \
			expand/db_quotes.c \
			header.c \
			main.c )
 
OBJS		= $(SRCS:.c=.o)

%.o			: %.c
			@$(CC) $(MAIN_INC) $(LIB_INC) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS)
			@make --silent -C $(LIB_DIR)
			@$(CC) $(OBJS) $(LIB_NAME) -L$(LIB_DIR) $(LIB_INC) $(MAIN_INC) -o $(NAME)
			@echo "minishell compiled"

clean:
			@$(MAKE) clean --silent -C $(LIB_DIR)
			@$(RM) $(OBJS)

fclean		: clean
			@$(MAKE) fclean --silent -C $(LIB_DIR)
			@$(RM) $(NAME)

re			: fclean all

norme		:
			@norminette $(SRCS)

.PHONY		: all clean fclean re docu
