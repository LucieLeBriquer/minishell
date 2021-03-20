/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:41:10 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/20 11:47:55 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <stdarg.h>
# include "libftstruct.h"
# define NB_SEPS 6
# define NB_TYPES 4
# define NB_BUILTIN 7
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct		s_parse
{
	char			sep;
	int				len_word;
	int				nb;
	int				state;
}					t_parse;

typedef struct		s_split
{
	char			*str;
	char			sep;
	int				space;
}					t_split;

typedef struct		s_env
{
	char			*var;
	char			*value;
	int				exported;
}					t_env;

typedef struct		s_info
{
	int				type;
	int				input;
	int				output;
	int				start;
	int				number;
	int				builtin;
	char			*line;
	void			*root;
	char			**args;
	char			*seps;
	int				*spaces;
	int				nb_args;
	char			**args_tmp;
	char			*seps_tmp;
	int				*spaces_tmp;
	int				nb_args_tmp;
	char			**argv;
	char			**env;
	char			*file_error;
	int				err;
	int				errno_save;
	char			*first_word;
	int				start_args;
	int				offset;
	int				is_subprocess;
	char			*all;
	t_split			*split;
}					t_info;

typedef struct		s_tree
{
	t_info			*info;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct		s_error
{
	int				num;
	char			token;
}					t_error;

typedef int	(*t_exec)(t_info *cmd, t_list **envl);

enum	{CMD, PIPE, LEFT, RIGHT, RRIGHT, SEMIC};
enum	{BUILTIN, EXECUTABLE, DECLARATION, EXECBIN};
enum	{ECHO, CD, PWD, EXPORT, UNSET, ENV, EXIT};
enum	{RESET, SPACE, QUOTE, DB_QUOTE, REDIR, OPERATOR};
enum	{SUCCESS = 0, PIPE_FAIL = 3, FORK_FAIL = 4, ALLOCATION_FAIL = 5,
	SYNTAX_QUOTES = 6, SYNTAX_REDIR = 7, AMBIGUOUS_REDIR = 8,
	TOOMANY = 24, ERROR = 1, MISUSE = 2, CANTEXEC = 126,
	NOTFOUND = 127, CSIGINT = 130};

#endif
