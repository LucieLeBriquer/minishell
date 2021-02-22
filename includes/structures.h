/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:41:10 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/22 23:33:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# define NB_SEPS 6
# define NB_TYPES 4
# define NB_BUILTIN 7

typedef struct		s_parse
{
	char			sep;
	int				nb_words;
	int				state;
}					t_parse;

typedef struct		s_split
{
	char			*str;
	char			quote;
	int				space;
}					t_split;

/*
** rename quote en sep
*/

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
}					t_info;

typedef struct		s_tree
{
	t_info			*info;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;


typedef int (*t_exec)(t_info *, t_split *, t_list **);

enum	{CMD, PIPE, LEFT, RIGHT, RRIGHT, SEMIC};
enum	{BUILTIN, EXECUTABLE, DECLARATION, EXECBIN};
enum	{ECHO, CD, PWD, EXPORT, UNSET, ENV, EXIT};

#endif
