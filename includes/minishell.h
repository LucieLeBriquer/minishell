/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:41:10 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/04 16:42:09 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libftfull.h"
# include <stdlib.h>
# define NB_CMD 3
# define SIZE_PATH 60

enum operators {PIPE = 1, LEFT, RIGHT, RRIGHT, SEMIC};

typedef struct
{
	char	*str;
	char	quote; // rename en sep
}			t_split;

typedef struct
{
	char	sep;
	int		nb_words;
	int		state;
}			t_parse;

typedef struct
{
	char	*name;
	char	*value;
}			t_env;

typedef struct
{
	int		type;
	int		input;
	int		output;
	int		start;
	int		number;
}			t_info;

typedef struct s_tree
{
	t_info			*info;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;


void		simple_parse(char *command);
t_split		*parse_quotes(char *command, int *err);
void		print_parse_quotes(char *command);
void		trim_spaces_right(char *s);
void		trim_useless(t_split split);
int			nb_words(char *s, int l);
int			len_of_word(char *s, char *sep, int l);
void		parse_env(t_list **env_list, char **env);
void		print_entry(void *ventry);
void		free_entry(void *ventry);
char		*search_env(t_list *env, char *to_find);
void		execute(t_split *split, char **env);
void		print_error_parsing(int err);
void		print_parsed_command(t_split *split);
t_tree		*create_tree(t_split *split);
void		print_tree(t_tree *tree, t_split *split);

#endif
