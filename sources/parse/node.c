/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:58:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 22:41:52 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*init_node(int i, int type, int number, char *line)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->type = type;
	info->input = 0;
	info->output = 1;
	info->start = i;
	info->number = number;
	info->builtin = 0;
	info->line = line;
	info->root = NULL;
	info->args = NULL;
	info->argv = NULL;
	info->seps = NULL;
	info->nb_args = 1;
	info->env = NULL;
	info->spaces = NULL;
	info->file_error = NULL;
	info->err = 0;
	info->first_word = NULL;
	info->start_args = 0;
	info->offset = 0;
	info->split = NULL;
	return (info);
}

t_tree	*create_leave(int start, int number, char *line)
{
	t_tree	*new;
	t_info	*new_info;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new_info = init_node(start, 0, number, line);
	new->left = NULL;
	new->right = NULL;
	new->info = new_info;
	return (new);
}

t_tree	*create_node(int i, int type, int start, char *line)
{
	t_tree		*new;
	t_info		*new_info;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new_info = init_node(i, type, 1, line);
	new->left = create_leave(start, i - start, line);
	new->right = NULL;
	new->info = new_info;
	return (new);
}
