/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 18:06:09 by lle-briq         ###   ########.fr       */
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
		close(cmd->input);
	if (cmd->output != 1)
		close(cmd->output);
}

void	fd_recursive(t_tree *tree, t_split *split, t_list **envl)
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
		if (PRINT_ALL == 1)
			ft_printf("create pipe [%d,%d]\n", pfd[0], pfd[1]);
		tree->left->info->output = pfd[1];
		fill_subtree_fd(tree->right, 0, pfd[0]);
	}
	fd_recursive(tree->left, split, envl);
	fd_recursive(tree->right, split, envl);
}

void	execute_recursive(t_tree *tree, t_split *split, t_list **envl)
{
	if (!tree)
		return ;
	execute_recursive(tree->left, split, envl);
	if (tree->info->type == CMD)
	{
		execute_cmd(tree->info, split, envl);
		close_unused_fd(tree->info);
		return ;
	}
	execute_recursive(tree->right, split, envl);
}

void	free_tree(t_tree *tree)
{
	t_info	*cmd;

	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	cmd = tree->info;
	if (cmd->args)
		free(cmd->args);
	if (cmd->env)
		free_tab(cmd->env);
	if (cmd->spaces)
		free(cmd->spaces);
	free(cmd);
	free(tree);
}

void	execute(t_split *split, t_list **envl, char *line)
{
	t_tree	*tree;

	tree = create_tree(split, line);
	fd_recursive(tree, split, envl);
	execute_recursive(tree, split, envl);
	while (wait(NULL) > 0)
		;
	free_tree(tree);
}
