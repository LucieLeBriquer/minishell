/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:41:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 16:21:35 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_one(char *to_unset, t_list *envl)
{
	t_list	*previous;

	previous = envl;
	envl = envl->next;
	while (envl)
	{
		if (variable_match(envl, to_unset, 0))
		{
			previous->next = envl->next;
			free_entry(envl->content);
			free(envl);
			return ;
		}
		previous = envl;
		envl = envl->next;
	}
}

int		ft_unset(t_info *cmd, t_list **envl)
{
	int		i;
	int		ret;

	if (cmd->number <= 1)
		return (0);
	if (create_tab_args(cmd))
		return (ALLOCATION_FAIL);
	i = 1;
	ret = 0;
	while (cmd->argv[i])
	{
		if (authorized_char(cmd->argv[i]) && !ft_strchr(cmd->argv[i], '='))
			unset_one(cmd->argv[i], *envl);
		else
		{
			ft_printf_fd(2, "minishell: unset: '%s': \
				not a valid identifier\n", cmd->argv[i]);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
