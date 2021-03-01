/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 19:48:51 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_subtree_fd(t_tree *tree, int out, int fd)
{
	if (!tree)
		return ;
	fill_subtree_fd(tree->left, out, fd);
	if (out)
		tree->info->output = fd;
	else
		tree->info->input = fd;
	fill_subtree_fd(tree->left, out, fd);
}

void		pipe_recursive(t_tree *tree, t_split *split, t_list **envl)
{
	int	pfd[2];
	int	type;

	if (!tree)
		return ;
	type = tree->info->type;
	if (type == CMD)
		return ;
	if (type == SEMIC)
	{
		fill_subtree_fd(tree->right, 0, 0);
		fill_subtree_fd(tree->right, 1, 1);
	}
	else
	{
		pipe(pfd);
		if (g_print_all == 1)
			ft_printf("create pipe [%d,%d]\n", pfd[0], pfd[1]);
		tree->left->info->output = pfd[1];
		fill_subtree_fd(tree->right, 0, pfd[0]);
	}
	pipe_recursive(tree->left, split, envl);
	pipe_recursive(tree->right, split, envl);
}
