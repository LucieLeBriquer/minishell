/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:49:15 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 17:40:39 by lle-briq         ###   ########.fr       */
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
	int		fd;

	errno = 0;
	fd = open(cmd->args[0], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("minishell: %s: %s\n", cmd->args[0], strerror(errno));
		return (-1);
	}
	close(fd);
	fork_and_exec(cmd, *envl, NULL);
	return (0);
}

int	exec_declaration(t_info *cmd, t_list **envl)
{
	int		i;

	if (create_tab_args(cmd) < 0)
		return (ALLOCATION_FAIL);
	i = 0;
	while (cmd->argv[i] && ft_strchr(cmd->argv[i], '='))
		i++;
	if (cmd->argv[i])
		ft_printf("still some work here...\n");
	else
		export_all(cmd->argv, envl, 0);
	return (0);
}

int	exec_execbin(t_info *cmd, t_list **envl)
{
	char	*file;

	if (open_executable(cmd, *envl, &file) < 0)
	{
		ft_printf("minishell: %s: command not found\n", cmd->args[0]);
		return (-1);
	}
	fork_and_exec(cmd, *envl, file);
	free(file);
	return (0);
}
