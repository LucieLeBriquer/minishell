/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:49:15 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/20 11:28:18 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_info *cmd, t_list **envl)
{
	t_exec	builtin[NB_BUILTIN];

	builtin[ECHO] = &ft_echo;
	builtin[CD] = &ft_cd;
	builtin[PWD] = &ft_pwd;
	builtin[EXPORT] = &ft_export;
	builtin[UNSET] = &ft_unset;
	builtin[ENV] = &ft_env;
	builtin[EXIT] = &ft_exit;
	return (builtin[cmd->builtin](cmd, envl));
}

int	exec_executable(t_info *cmd, t_list **envl)
{
	if (ft_strcmp(cmd->argv[cmd->offset], "./minishell") == 0)
		g_signal = 6;
	return (fork_and_exec(cmd, *envl, NULL));
}

int	exec_declaration(t_info *cmd, t_list **envl)
{
	int		i;
	t_exec	exec_func[NB_TYPES];

	exec_func[BUILTIN] = &exec_builtin;
	exec_func[EXECUTABLE] = &exec_executable;
	exec_func[DECLARATION] = &exec_declaration;
	exec_func[EXECBIN] = &exec_execbin;
	i = 0;
	while (cmd->argv[i] && ft_strchr(cmd->argv[i], '='))
		i++;
	if (cmd->argv[i])
	{
		cmd->offset = i;
		return (exec_func[cmd_type(cmd, i)](cmd, envl));
	}
	else if (!cmd->is_subprocess)
		return (export_all(cmd->argv, envl, 0));
	return (SUCCESS);
}

int	exec_execbin(t_info *cmd, t_list **envl)
{
	char	*file;
	int		err;

	if (open_executable(cmd, *envl, &file))
	{
		if (file)
			free(file);
		print_error(cmd->argv[cmd->offset], NULL, 0, "command not found");
		return (NOTFOUND);
	}
	err = fork_and_exec(cmd, *envl, file);
	free(file);
	return (err);
}
