/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/13 18:25:03 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_subtree_fd(t_tree *tree, int out, int fd, int is_sub)
{
	if (!tree)
		return ;
	if (out)
		tree->info->output = fd;
	else
		tree->info->input = fd;
	tree->info->is_subprocess = is_sub;
	fill_subtree_fd(tree->left, out, fd, is_sub);
}

int			pipe_recursive(t_tree *tree, t_split *split, t_list **envl)
{
	int	pfd[2];
	int	type;

	if (!tree)
		return (SUCCESS);
	type = tree->info->type;
	if (type == CMD)
		return (SUCCESS);
	if (type == SEMIC)
	{
		fill_subtree_fd(tree->right, 0, 0, 0);
		fill_subtree_fd(tree->right, 1, 1, 0);
	}
	else
	{
		if (pipe(pfd))
			return (PIPE_FAIL);
		tree->left->info->output = pfd[1];
		tree->left->info->is_subprocess = 1;
		fill_subtree_fd(tree->right, 0, pfd[0], 1);
	}
	if (pipe_recursive(tree->left, split, envl)
		|| pipe_recursive(tree->right, split, envl))
		return (PIPE_FAIL);
	return (SUCCESS);
}
