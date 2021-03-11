/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:48:35 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/11 19:51:15 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_and_exec(t_info *cmd, t_list *envl, char *file)
{
	int		pid;
	char	**argv;

	cmd->env = create_env_tab(envl, 0);
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		errno = 0;
		argv = cmd->argv + cmd->offset;
		if (file)
			return (execve(file, argv, cmd->env));
		else
			return (execve(cmd->args[cmd->offset], argv, cmd->env));
	}
	return (0);
}
