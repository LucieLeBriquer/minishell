/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/13 17:07:08 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_subtree_fd(t_tree *tree, int out, int fd)
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

void	close_unused_fd(t_info *cmd)
{
	if (cmd->input != 0)
	{
		ft_printf("closing %d...\n", cmd->input);
		close(cmd->input);
	}
	if (cmd->output != 1)
	{
		ft_printf("closing %d...\n", cmd->output);
		close(cmd->output);
	}
	ft_printf("\n");
}

void	execute_recursive(t_tree *tree, t_split *split, char **env)
{
	int	pfd[2];
	int	type;

	if (!tree)
		return ;
	type = tree->info->type;
	if (type == CMD)
	{
		execute_cmd(tree->info, split, env);
		close_unused_fd(tree->info);
		return ;
	}
	if (type == SEMIC)
	{
		fill_subtree_fd(tree->right, 0, 0);
		fill_subtree_fd(tree->right, 1, 1);
	}
	else
	{
		pipe(pfd);
		tree->left->info->output = pfd[1];
		fill_subtree_fd(tree->right, 0, pfd[0]);
	}
	execute_recursive(tree->left, split, env);
	execute_recursive(tree->right, split, env);
}

void	execute(t_split *split, char **env)
{
	t_tree	*tree;

	tree = create_tree(split);
	execute_recursive(tree, split, env);
}
