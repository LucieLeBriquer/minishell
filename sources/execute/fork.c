/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:48:35 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/13 18:23:25 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_and_exec(t_info *cmd, t_list *envl, char *file)
{
	int		pid;
	char	**argv;
	char	*to_exec;
	int		err;

	cmd->env = create_env_tab(envl, 0);
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		errno = 0;
		argv = cmd->argv + cmd->offset;
		to_exec = cmd->args[cmd->offset];
		if (file)
			to_exec = file;
		err = execve(to_exec, argv, cmd->env);
		print_error(to_exec, NULL, errno, NULL);
		if (errno == 2)
			exit(NOTFOUND);
		else
			exit(CANTEXEC);
	}
	return (SUCCESS);
}
