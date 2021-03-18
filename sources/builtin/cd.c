/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:39:19 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/18 15:54:43 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_list *envl)
{
	char	*path_home;

	path_home = search_in_env(envl, "HOME");
	if (!path_home)
	{
		print_error("minishell: cd", NULL, 0, "HOME not set");
		return (ERROR);
	}
	errno = 0;
	if (chdir(path_home))
	{
		print_error("cd", path_home, errno, NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

int			ft_cd(t_info *cmd, t_list **envl)
{
	int		err;
	char	*path;

	if (number_of_args(cmd->argv + cmd->offset) > 2)
	{
		ft_printf("minishell: '%s': %s\n", "cd", "too many arguments");
		return (MISUSE);
	}
	if (cmd->args[cmd->offset + 1])
	{
		path = cmd->argv[cmd->offset + 1];
		errno = 0;
		err = chdir(path);
		if (err)
		{
			print_error("cd", cmd->argv[cmd->offset + 1], errno, NULL);
			return (ERROR);
		}
		return (SUCCESS);
	}
	return (cd_home(*envl));
}
