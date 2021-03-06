/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/06 11:53:20 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_recursive(t_tree *tree, t_split *split, t_list **envl)
{
	int	err;

	if (!tree)
		return (0);
	if (tree->info->type == CMD)
	{
		err = execute_cmd(tree->info, split, envl);
		close_unused_fd(tree->info);
		return (err);
	}
	(void)execute_recursive(tree->left, split, envl);
	return (execute_recursive(tree->right, split, envl));
}

int			execute(t_split *split, t_list **envl, char *line)
{
	t_tree	*tree;
	int		status;
	int		err;

	tree = create_tree(split, line);
	pipe_recursive(tree, split, envl);
	err = execute_recursive(tree, split, envl);
	while (wait(&status) > 0)
		;
	free_tree(tree);
	if (status)
		err = status / 256;
	print_child_end(err);
	return (err);
}
