/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 16:47:49 by lle-briq         ###   ########.fr       */
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

void		execute(t_split *split, t_list **envl, char *line)
{
	t_tree	*tree;
	int		status;

	ft_putstr(WHITE);
	tree = create_tree(split, line);
	pipe_recursive(tree, split, envl);
	execute_recursive(tree, split, envl);
	while (wait(&status) > 0)
		;
	free_tree(tree);
	print_child_end(status);
}
