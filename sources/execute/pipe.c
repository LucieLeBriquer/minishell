/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/11 21:11:36 by lle-briq         ###   ########.fr       */
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
		fill_subtree_fd(tree->right, 0, 0);
		fill_subtree_fd(tree->right, 1, 1);
	}
	else
	{
		errno = 0;
		if (pipe(pfd))
			return (PIPE_FAIL);
		if (g_print_all == 1)
			ft_printf("%screate pipe [%d,%d]%s\n", GREY, pfd[0], pfd[1], WHITE);
		tree->left->info->output = pfd[1];
		fill_subtree_fd(tree->right, 0, pfd[0]);
	}
	if (pipe_recursive(tree->left, split, envl)
		|| pipe_recursive(tree->right, split, envl))
		return (PIPE_FAIL);
	return (SUCCESS);
}
