/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 18:13:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_recursive(t_tree *tree, t_split *split, t_list **envl)
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
	pipe_recursive(tree, split, envl);
	execute_recursive(tree, split, envl);
	while (wait(NULL) > 0)
		;
	free_tree(tree);
}
