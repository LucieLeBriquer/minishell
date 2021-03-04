/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:41:10 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 16:09:35 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <stdarg.h>
# include "libftstruct.h"
# define NB_SEPS 6
# define NB_TYPES 4
# define NB_BUILTIN 7
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
	char			**argv;
	char			*seps;
	int				nb_args;
	char			**env;
	int				*spaces;
	char			*file_error;
	int				err;
	char			*first_word;
	int				start_args;
}					t_info;

typedef struct		s_tree
{
	t_info			*info;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef int	(*t_exec)(t_info *cmd, t_list **envl);

enum	{CMD, PIPE, LEFT, RIGHT, RRIGHT, SEMIC};
enum	{BUILTIN, EXECUTABLE, DECLARATION, EXECBIN};
enum	{ECHO, CD, PWD, EXPORT, UNSET, ENV, EXIT};
enum	{FORK_FAIL = -2, ALLOCATION_FAIL = -3};
enum	{RESET, SPACE, QUOTE, DB_QUOTE, REDIR, OPERATOR};

#endif
