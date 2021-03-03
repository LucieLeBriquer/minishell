/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:06:38 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/03 17:11:52 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	declare(char *to_export, t_env *var)
{
	if (ft_strchr(to_export, '='))
	{
		if (var->value)
			free(var->value);
		var->value = ft_strdup(ft_strchr(to_export, '=') + 1);
	}
}

static void	export_one(char *to_export, t_list *envl)
{
	char	*empty;
	t_list	*save;
	t_list	*new;

	save = envl;
	while (envl)
	{
		save = envl;
		if (variable_match(envl, to_export, 1))
		{
			((t_env *)envl->content)->exported = 2;
			declare(to_export, envl->content);
			return ;
		}
		envl = envl->next;
	}
	empty = ft_strdup(to_export);
	new = init_entry(empty, 1);
	if (((t_env *)new->content)->value != NULL)
		((t_env *)new->content)->exported = 2;
	free(empty);
	save->next = new;
}

static void	unvalid_identifier(char *str, int *ret)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	*ret = 1;
}*/

int			ft_export(t_info *cmd, t_split *split, t_list **envl)
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
