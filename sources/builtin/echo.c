/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:39:28 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 16:23:08 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args, int option, int i)
{
	while (args[i] && args[i + 1])
	{
		ft_printf("%s", args[i]);
		i++;
	}
	if (args[i])
		ft_printf("%s", args[i]);
	if (!option)
		ft_printf("\n");
}

static int	option_echo(t_info *cmd)
{
	int	i;

	i = 1;
	while ((cmd->args)[i] && (ft_strcmp((cmd->args)[i], "-n") == 0))
		i++;
	return (i);
}

int			ft_echo(t_info *cmd, t_list **envl)
{
	int		i;
	int		pid;

	(void)envl;
	i = option_echo(cmd);
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		if (create_tab_args(cmd))
			return (ALLOCATION_FAIL);
		print_args(cmd->argv, (i > 1), i);
		exit(0);
	}
	return (0);
}
