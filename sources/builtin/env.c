/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:39:32 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 19:42:31 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			{
				ft_printf("declare -x %s", entry->var);
				if (entry->value)
					ft_printf("=\"%s\"", entry->value);
				ft_printf("\n");
			}
			else if (!declare && entry->exported >= 2)
				ft_printf("%s=%s\n", entry->var, entry->value);
		}
		envl = envl->next;
	}
}

int		ft_env(t_info *cmd, t_split *split, t_list **envl)
{
	int		pid;

	cmd->args = create_tab_args(cmd, split);
	if (number_of_args(cmd->args) > 1)
	{
		ft_printf("env: should be used without option and argument\n");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_envl(*envl, 0);
		exit(0);
	}
	return (0);
}
