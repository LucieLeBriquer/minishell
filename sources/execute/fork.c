/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:48:35 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 22:02:41 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_and_exec(t_info *cmd, t_split *split, t_list *envl, char *file)
{
	int		ret;
	int		pid;

	cmd->env = create_env_tab(envl, 0);
	ret = -1;
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		cmd->args = create_tab_args(cmd, split);
		if (file)
			ret = execve(file, cmd->args, cmd->env);
		else
			ret = execve(split[cmd->start].str, cmd->args, cmd->env);
	}
	return (0);
}
