/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:06:38 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/03 18:51:35 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_identifier(char *str)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

int		ft_export(t_info *cmd, t_split *split, t_list **envl)
{
	cmd->args = create_tab_args(cmd, split);
	cmd->nb_args = number_of_args(cmd->args);
	cmd->spaces = create_tab_spaces(cmd, split);
	if (number_of_args(cmd->args) <= 1)
		return (print_sorted(*envl, cmd));
	return (multiple_var(*cmd, envl));
}

/*
** modifier l'export/les declaration d'un en prenant en compte les arguments
** multiples dans le cas a="reverve"
** while no space, ajouter des elements
*/
