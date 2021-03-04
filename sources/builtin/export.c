/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:06:38 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 17:40:04 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(t_info *cmd, t_list **envl)
{
	if (create_tab_args(cmd))
		return (ALLOCATION_FAIL);
	if (number_of_args(cmd->argv) <= 1)
		return (print_sorted(*envl, cmd));
	return (export_all(cmd->argv + 1, envl, 2));
}
