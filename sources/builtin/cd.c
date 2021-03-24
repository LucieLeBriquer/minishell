/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:39:19 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/24 15:13:16 by lle-briq         ###   ########.fr       */
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

static int	cd_old(t_list *envl)
{
	char	*path_old;

	path_old = search_in_env(envl, "OLDPWD");
	if (!path_old)
	{
		print_error("minishell: cd", NULL, 0, "OLDPWD not set");
		return (ERROR);
	}
	errno = 0;
	ft_putstr_fd(path_old, STDERR);
	ft_putstr_fd("\n", STDERR);
	if (chdir(path_old))
	{
		print_error("cd", path_old, errno, NULL);
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
		print_error("minishell: cd", NULL, 0, "too many arguments");
		return (MISUSE);
	}
	if (cmd->args[cmd->offset + 1])
	{
		path = cmd->argv[cmd->offset + 1];
		errno = 0;
		if (ft_strcmp("-", path) == 0)
			return (cd_old(*envl));
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
