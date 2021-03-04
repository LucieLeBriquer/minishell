/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:06:38 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 17:18:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_identifier(char *str)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

int		ft_export(t_info *cmd, t_list **envl)
{
	if (create_tab_args(cmd))
		return (ALLOCATION_FAIL);
	if (number_of_args(cmd->argv) <= 1)
		return (print_sorted(*envl, cmd));
	return (export_all(cmd->argv + 1, envl));
}
