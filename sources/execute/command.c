/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:48:01 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/11 21:35:52 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(str, "cd") == 0)
		return (CD);
	if (ft_strcmp(str, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(str, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(str, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(str, "env") == 0)
		return (ENV);
	if (ft_strcmp(str, "exit") == 0)
		return (EXIT);
	return (-1);
}

int			cmd_type(t_info *cmd, int i)
{
	cmd->builtin = is_builtin(cmd->argv[i]);
	if (cmd->builtin > -1)
		return (BUILTIN);
	if (ft_strchr(cmd->argv[i], '='))
		return (DECLARATION);
	if (is_path(cmd->argv[i]))
		return (EXECUTABLE);
	else
		return (EXECBIN);
}

static int	error_in_out(t_info *cmd)
{
	if (cmd->err)
		print_error(cmd->file_error, cmd->err, NULL);
	else
		print_error(NULL, 0, "syntax error near unexpected token `newline'\n");
	return (-1);
}

int			execute_cmd(t_info *cmd, t_split *split, t_list **envl)
{
	t_exec	exec_func[NB_TYPES];
	int		err;

	exec_func[BUILTIN] = &exec_builtin;
	exec_func[EXECUTABLE] = &exec_executable;
	exec_func[DECLARATION] = &exec_declaration;
	exec_func[EXECBIN] = &exec_execbin;
	print_leave(*cmd, split, 0);
	cmd->split = split;
	if (g_sigint)
	{
		add_env("?begin", ft_strdup("130"), envl, -1);
		g_sigint = 0;
	}
	expand(cmd, split, *envl);
	print_leave(*cmd, split, 1);
	err = join_words(cmd, split);
	if (err)
		return (-1);
	if (update_in_out(cmd) < 0)
		return (error_in_out(cmd));
	if (create_tab_args(cmd))
		return (ALLOCATION_FAIL);
	errno = 0;
	return ((exec_func[cmd_type(cmd, 0)])(cmd, envl));
}
