/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:39:32 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/18 16:00:15 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_quoted(t_env entry)
{
	ft_putstr("declare -x ");
	ft_putstr(entry.var);
	if (entry.value)
	{
		ft_putstr("=\"");
		ft_putstr(entry.value);
		ft_putstr("\"");
	}
	ft_putstr("\n");
}

static void	print_unquoted(t_env entry)
{
	ft_putstr(entry.var);
	ft_putstr("=");
	ft_putstr(entry.value);
	ft_putstr("\n");
}

void	print_envl(t_list *envl, int declare)
{
	t_env	*entry;

	while (envl)
	{
		entry = (t_env *)envl->content;
		if (authorized_char(entry->var))
		{
			if (declare && entry->exported >= 1
				&& ft_strcmp(entry->var, "_") != 0)
				print_quoted(*entry);
			else if (!declare && entry->exported >= 2)
				print_unquoted(*entry);
		}
		envl = envl->next;
	}
}

int		ft_env(t_info *cmd, t_list **envl)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (number_of_args(cmd->argv + cmd->offset) > 1)
		{
			print_error("env", NULL, 0,\
			"should be used without option and argument");
			exit(MISUSE);
		}
		change_stdin_stdout(cmd);
		print_envl(*envl, 0);
		exit(SUCCESS);
	}
	return (SUCCESS);
}
