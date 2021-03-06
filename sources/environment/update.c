/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 11:43:41 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/24 14:44:11 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_return(t_list **envl, int err)
{
	if (g_signal == 2)
		add_env("?begin", ft_itoa(130), envl, -1);
	else
		add_env("?begin", ft_itoa(err), envl, -1);
}

int		get_return(t_list *envl)
{
	return (ft_atoi(search_in_env(envl, "?begin")));
}

void	update_env(t_list **envl)
{
	char	*pwd;
	char	cwd[SIZE_PATH];

	pwd = search_in_env(*envl, "PWD");
	if (!pwd)
		return ;
	getcwd(cwd, SIZE_PATH);
	if (ft_strcmp(pwd, cwd) != 0)
	{
		add_env("OLDPWD", ft_strdup(pwd), envl, 1);
		add_env("PWD", ft_strdup(cwd), envl, 1);
	}
}

void	update_last_arg(t_list **envl, t_info *cmd, t_split *split)
{
	int	i;

	if (cmd)
		i = cmd->start - 1;
	else
	{
		i = 0;
		while (split[i].str)
			i++;
		i--;
	}
	if (i >= 0)
		add_env("_", ft_strdup(split[i].str), envl, 1);
}
