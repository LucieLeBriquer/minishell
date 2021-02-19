/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:41:10 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/19 17:09:00 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libftfull.h"
# include "structures.h"
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# define NB_CMD 3
# define SIZE_PATH 60

int		PRINT_ALL;

void	simple_parse(char *command);
t_split	*parse_command(char *command, int *err);
void	print_parse_quotes(char *command);
void	trim_spaces_right(char *s);
void	trim_spaces_left(char *s);
void	trim_useless(t_split split);
int		nb_words(char *s, int l);
int		len_of_word(char *s, char *sep);
void	parse_env(t_list **env_list, char **env);
void	print_entry(void *ventry);
void	free_entry(void *ventry);
t_list	*init_entry(char *line, int exported);
char	*search_env(t_list *env, char *to_find);
void	execute(t_split *split, t_list *envl);
void	print_error_parsing(int err);
void	print_parsed_command(t_split *split);
t_tree	*create_tree(t_split *split);
void	print_tree(t_tree *tree, t_split *split);
void	execute_cmd(t_info *, t_split *, t_list *envl);
int		exec_builtin(t_info *, t_split *, t_list *envl);
int		exec_executable(t_info *, t_split *, t_list *envl);
int		exec_declaration(t_info *, t_split *, t_list *envl);
int		exec_execbin(t_info *, t_split *, t_list *envl);
int		update_in_out(t_info *cmd, t_split *split);
int		open_executable(t_info *cmd, t_split *split, char **env, char **file);
char	**create_tab_args(t_info *cmd, t_split *split);
void	close_unused_fd(t_info *cmd);
void	change_stdin_stdout(t_info *cmd);
void	print_child_end(int status);
int		number_of_args(char **args);
void	free_tab(char **args);
char	*search_in_env(t_list *envl, char *var);
char	**create_env_tab(t_list *envl, int exported);
int		is_in_env(t_list *envl, char *var);
int		is_path(char *word);

/*
** Built-in
*/

int		ft_cd(t_info *, t_split *, t_list *envl);
int		ft_echo(t_info *, t_split *, t_list *envl);
int		ft_env(t_info *, t_split *, t_list *envl);
int		ft_exit(t_info *, t_split *, t_list *envl);
int		ft_export(t_info *, t_split *, t_list *envl);
int		ft_pwd(t_info *, t_split *, t_list *envl);
int		ft_unset(t_info *, t_split *, t_list *envl);

#endif
