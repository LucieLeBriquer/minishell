CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
NAME		= libft.a
LIB			= ar rcs
NORME		= ~/.norminette_v2/norminette.rb

INCS_DIR	= includes/
INCS		= $(addprefix $(INCS_DIR), libftfull.h libftstruct.h)

SRCS		= convert/ft_atoi.c \
			  convert/ft_itoa.c \
			  convert/ft_max.c \
			  convert/ft_min.c \
			  convert/ft_tolower.c \
			  convert/ft_toupper.c \
			  convert/ft_utoa.c \
			  convert/ft_utoct.c \
			  convert/ft_utox.c \
			  convert/ft_utoxx.c \
			  gnl/get_next_line.c \
			  gnl/get_next_line_utils.c \
			  list/ft_lstadd_back.c \
			  list/ft_lstadd_front.c \
			  list/ft_lstclear.c \
			  list/ft_lstdelone.c \
			  list/ft_lstiter.c \
			  list/ft_lstlast.c \
			  list/ft_lstmap.c \
			  list/ft_lstnew.c \
			  list/ft_lstsize.c \
			  memory/ft_bzero.c \
			  memory/ft_calloc.c \
			  memory/ft_memccpy.c \
			  memory/ft_memchr.c \
			  memory/ft_memcmp.c \
			  memory/ft_memcpy.c \
			  memory/ft_memmove.c \
			  memory/ft_memset.c \
			  string/ft_split.c \
			  string/ft_splitchar.c \
			  string/ft_strchr.c \
			  string/ft_strdup.c \
			  string/ft_strjoin.c \
			  string/ft_strlcat.c \
			  string/ft_strlcpy.c \
			  string/ft_strlen.c \
			  string/ft_strmapi.c \
			  string/ft_strcmp.c \
			  string/ft_strncmp.c \
			  string/ft_strnstr.c \
			  string/ft_strrchr.c \
			  string/ft_strtrim.c \
			  string/ft_substr.c \
			  type/ft_isalnum.c \
			  type/ft_isalpha.c \
			  type/ft_isascii.c \
			  type/ft_isdigit.c \
			  type/ft_isprint.c \
			  type/ft_isspace.c \
			  type/ft_issep.c \
			  write/ft_putchar.c \
			  write/ft_putchar_fd.c \
			  write/ft_putendl.c \
			  write/ft_putendl_fd.c \
			  write/ft_putnbr.c \
			  write/ft_putnbr_fd.c \
			  write/ft_putstr.c \
			  write/ft_putstr_fd.c

PRINT_SRCS	= $(addprefix printf/, ft_printf.c ft_printf_fd.c \
			parse/errors.c \
			parse/params.c \
			print/print_0chr.c \
			print/print_1str.c \
			print/print_2ptr.c \
			print/print_3dbl.c \
			print/print_4int.c \
			print/print_5uns.c \
			print/print_6hex.c \
			print/print_7hexx.c \
			print/print_8pct.c \
			print/print_9oct.c \
			print/fun_print_str.c \
			print/fun_print_int.c \
			print/fun_print_int_bis.c \
			print/print.c \
			print/utils.c)


OBJS		= $(SRCS:.c=.o) $(PRINT_SRCS:.c=.o)

%.o			: %.c
			@$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS)
			@$(LIB) $(NAME) $(OBJS)

norme		:
			@$(NORME) $(SRCS) $(PRINT_SRCS) $(INCS)

clean:
			@$(RM) $(OBJS)

fclean		: clean
			@$(RM) $(NAME)

re			: fclean all

.PHONY		: all clean fclean re norme
