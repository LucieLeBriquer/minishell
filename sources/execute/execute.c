/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 23:46:08 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		draw_line(int n)
{
	int	i;

	i = -1;
	ft_putstr("\033[30m");
	while (++i < n)
		ft_putstr("\xE2\x94\x80");
	ft_putstr(WHITE);
	ft_putstr("\n");
}

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
	if (g_print_all)
		draw_line(84);
}

void		execute(t_split *split, t_list **envl, char *line)
{
	t_tree	*tree;
	int		status;

	tree = create_tree(split, line);
	pipe_recursive(tree, split, envl);
	execute_recursive(tree, split, envl);
	if (g_print_all && tree->info->type == CMD)
		draw_line(84);
	while (wait(&status) > 0)
		;
	draw_line(84);
	print_child_end(status);
	free_tree(tree);
}
