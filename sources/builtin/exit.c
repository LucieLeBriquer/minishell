/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:39:36 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 22:40:30 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_info *cmd, t_list **envl)
{
	ft_printf("exit\n");
	free_all(cmd->line, cmd->split);
	free_tree(cmd->root);
	ft_lstclear(envl, &free_entry);
	exit(0);
	return (0);
}
