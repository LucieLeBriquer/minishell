/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:41:10 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/10 16:51:31 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libftfull.h"
# include "structures.h"
# include <stdlib.h>
# include <signal.h>
# define NB_CMD 3
# define SIZE_PATH 60

void		simple_parse(char *command);
t_split		*parse_command(char *command, int *err);
void		print_parse_quotes(char *command);
void		trim_spaces_right(char *s);
void		trim_spaces_left(char *s);
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
void		execute_cmd(t_info *cmd, t_split *split, char **env);
void	exec_builtin(t_info *cmd, t_split *split, char **env);
void	exec_executable(t_info *cmd, t_split *split, char **env);
void	exec_declaration(t_info *cmd, t_split *split, char **env);
void	exec_execbin(t_info *cmd, t_split *split, char **env);


#endif
