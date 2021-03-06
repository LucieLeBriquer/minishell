/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:39:36 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/20 10:47:53 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	free_exit(t_info *cmd, t_list **envl)
{
	ft_putstr("exit\n");
	free_all(cmd->line, cmd->split);
	free_tree(cmd->root);
	ft_lstclear(envl, &free_entry);
}

int			ft_exit(t_info *cmd, t_list **envl)
{
	int	exit_value;

	if (number_of_args(cmd->argv) < 2)
	{
		exit_value = ft_atoi(search_in_env(*envl, "?begin"));
		free_exit(cmd, envl);
		exit(exit_value);
	}
	else if (!ft_isnum(cmd->argv[cmd->offset + 1]))
	{
		free_exit(cmd, envl);
		print_error("minishell: exit", NULL, 0, "numeric argument required");
		exit(MISUSE);
	}
	else if (number_of_args(cmd->argv) > 2)
	{
		ft_putstr("exit\n");
		print_error("minishell: exit", NULL, 0, "too many arguments");
		return (ERROR);
	}
	exit_value = ft_atoi(cmd->argv[cmd->offset + 1]);
	free_exit(cmd, envl);
	exit(exit_value);
}
