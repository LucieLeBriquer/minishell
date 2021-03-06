/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:48:01 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/24 14:55:25 by lle-briq         ###   ########.fr       */
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
	if (!cmd->argv[i])
		return (-1);
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
		print_error(NULL, cmd->file_error, cmd->err, NULL);
	else
		print_error(NULL, NULL, 0,\
		"syntax error near unexpected token `newline'\n");
	return (ERROR);
}

int			execute_cmd(t_info *cmd, t_split *split, t_list **envl)
{
	t_exec	exec_func[NB_TYPES];

	exec_func[BUILTIN] = &exec_builtin;
	exec_func[EXECUTABLE] = &exec_executable;
	exec_func[DECLARATION] = &exec_declaration;
	exec_func[EXECBIN] = &exec_execbin;
	if (g_signal)
		update_return(envl, 128 + g_signal);
	cmd->split = split;
	if (cmd->number == 0)
		return (SUCCESS);
	if (expand(cmd, *envl, split))
		return (ERROR);
	if (cmd->nb_args_tmp == 0)
		return (SUCCESS);
	if (update_in_out(cmd) < 0)
		return (error_in_out(cmd));
	if (create_tab_args(cmd))
		return (ERROR);
	if (cmd_type(cmd, 0) >= 0)
		return (exec_func[cmd_type(cmd, 0)])(cmd, envl);
	return (SUCCESS);
}
