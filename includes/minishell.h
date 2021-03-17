/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:41:10 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/17 18:02:08 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "structures.h"
# include "libftfull.h"
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# define NB_CMD 3
# define SIZE_PATH 4096
# define SQUARE "\xE2\x96\xA1 "
# define WHITE "\033[0;0m"
# define GREY "\033[0;30m"
# define COLOR "\033[0;35m"
# define BOLD "\033[1;35m"

int		g_print_all;
int		g_sigint;
int		g_sigquit;

void	simple_parse(char *command);
t_split	*parse_command(char *command, t_error *error);
void	print_parse_quotes(char *command);
void	parse_env(t_list **env_list, char **env);
void	print_entry(void *ventry);
void	free_entry(void *ventry);
void	free_tree(t_tree *tree);
t_list	*init_entry(char *line, int exported);
char	*search_env(t_list *env, char *to_find);
int		execute(t_split *split, t_list **envl, char *line);
void	print_error_parsing(t_error error);
void	print_parsed_command(t_split *split);
t_tree	*create_tree(t_split *split, char *line);
void	print_tree(t_tree *tree, t_split *split);
int		execute_cmd(t_info *cmd, t_split *split, t_list **envl);
int		exec_builtin(t_info *cmd, t_list **envl);
int		exec_executable(t_info *cmd, t_list **envl);
int		exec_declaration(t_info *cmd, t_list **envl);
int		exec_execbin(t_info *cmd, t_list **envl);
int		update_in_out(t_info *cmd);
int		open_executable(t_info *cmd, t_list *envl, char **file);
int		create_tab_args(t_info *cmd);
int		*create_tab_spaces(t_info *cmd, t_split *split);
void	close_unused_fd(t_info *cmd);
void	change_stdin_stdout(t_info *cmd);
void	print_child_end(int status);
int		number_of_args(char **args);
void	free_tab(char **args);
char	*search_in_env(t_list *envl, char *var);
char	**create_env_tab(t_list *envl, int exported);
int		variable_match(t_list *envl, char *var, int cut);
int		is_path(char *word);
int		authorized_char(char *s);
void	print_envl(t_list *envl, int declare);
int		print_sorted(t_list *envl, t_info *cmd);
void	free_all(char *line, t_split *split);
char	*search(char *var, t_list *envl);
int		reader(char **line);
void	ft_lstsort(t_list **begin_list, int (*cmp)());
int		fork_and_exec(t_info *cmd, t_list *envl, char *file);
void	print_leave(t_info cmd, t_split *split, int j);

/*
** Environment
*/

int		multiple_var(t_info cmd, t_list **envl);
int		export_all(char **vars, t_list **envl, int exported);
void	invalid_identifier(char *str, char *func, int exported);
int		add_env(char *var, char *value, t_list **envl, int exported);
int		list_size(t_list *lst);

/*
** Built-in
*/

int		ft_cd(t_info *cmd, t_list **envl);
int		ft_echo(t_info *cmd, t_list **envl);
int		ft_env(t_info *cmd, t_list **envl);
int		ft_exit(t_info *cmd, t_list **envl);
int		ft_export(t_info *cmd, t_list **envl);
int		ft_pwd(t_info *cmd, t_list **envl);
int		ft_unset(t_info *cmd, t_list **envl);

/*
** Parsing
*/

int		state_space(char *command, int i, t_parse *p);
int		state_quote(char *command, int i, t_parse *p);
int		state_db_quote(char *command, int i, t_parse *p);
int		state_operator(char *command, int i, t_parse *p);
int		state_reset(char *command, int i, t_parse *p);
int		nb_words(char *s);
int		len_of_word(char *s, int i, char *sep);
void	trim_seps(t_split split);
void	trim_spaces(char *s);
int		new_state(char *command, int i);
int		is_state_ok(t_parse *p);
int		is_spaceend(char c);
int		is_operator(char c);
char	sep_converter(char c, char *command, int k);
void	trim_seps(t_split split);

/*
** Tree
*/

t_tree	*create_node(int i, int type, int start, char *line);
t_tree	*create_leave(int start, int number, char *line);

/*
** Execute
*/

int		pipe_recursive(t_tree *tree, t_split *split, t_list **envl);
int		join_words(t_info *cmd, t_split *split);
int		cmd_type(t_info *cmd, int i);

/*
** Expand
*/

char	**create_env_tab(t_list *envl, int exported);
void	fill_expanded(char *fill, char *old, t_list *envl);
int		size_var(char *str, t_list *envl, char **value);

int		expand(t_info *cmd, t_list *envl, t_split *split);
int		expand_hard(t_list **expansion, t_split curr, t_list *envl, int r);
void	expand_simple(t_list **expansion, t_split curr, t_list *envl);
t_list	*new_entry(char *str, char sep, int space);
int		is_redir(char c);
void	free_expd(void *expd);

int		words(t_info *cmd, t_split *split);
int		join_args(t_info *cmd);
char	*char_to_string(char c);

/*
** Utilities
*/

void	print_title(char *s);
void	print_error(char *exe, char *file, int err, char *error);
void	prompt(void);
void	header(void);
void	free_lists(t_list **w, t_list **s, t_list **sp);

/*
** To delete
*/

void	print_tab(char **tab);
void	print_tabs(t_info cmd, int join);
void	print_expand(t_info cmd);


#endif
