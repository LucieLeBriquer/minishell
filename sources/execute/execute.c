/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/22 15:39:36 by lle-briq         ###   ########.fr       */
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
		if (PRINT_ALL == 1)
			ft_printf("closing %d...\n", cmd->input);
		close(cmd->input);
	}
	if (cmd->output != 1)
	{
		if (PRINT_ALL == 1)
			ft_printf("closing %d...\n", cmd->output);
		close(cmd->output);
	}
	if (PRINT_ALL == 1)
		ft_printf("\n");
}

void	execute_recursive(t_tree *tree, t_split *split, t_list **envl)
{
	int	pfd[2];
	int	type;

	if (!tree)
		return ;
	type = tree->info->type;
	if (type == CMD)
	{
		execute_cmd(tree->info, split, envl);
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
	execute_recursive(tree->left, split, envl);
	execute_recursive(tree->right, split, envl);
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree->info);
	free(tree);
}

void	execute(t_split *split, t_list **envl, char *line)
{
	t_tree	*tree;

	tree = create_tree(split, line);
	execute_recursive(tree, split, envl);
	free_tree(tree);
}
