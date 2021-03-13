/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/13 17:33:08 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_recursive(t_tree *tree, t_split *split, t_list **envl)
{
	int	err;
	int	status;

	if (!tree)
		return (0);
	err = execute_recursive(tree->left, split, envl);
	if (tree->info->type == CMD)
	{
		err = execute_cmd(tree->info, split, envl);
		close_unused_fd(tree->info);
		return (err);
	}
	if (tree->info->type == SEMIC)
	{
		add_env("?begin", ft_itoa(err), envl, -1);
		while (wait(&status) > 0)
			;
	}
	return (execute_recursive(tree->right, split, envl));
}

static void	remove_last_semic(t_split *split)
{
	int	i;

	i = 0;
	while (split[i].str)
		i++;
	if (i > 0 && split[i - 1].sep == ';')
	{
		split[i - 1].str = NULL;
		split[i - 1].sep = '\0';
	}
}

int			execute(t_split *split, t_list **envl, char *line)
{
	t_tree	*tree;
	int		status;
	int		err;

	status = 0;
	remove_last_semic(split);
	tree = create_tree(split, line);
	if (pipe_recursive(tree, split, envl))
	{
		free_tree(tree);
		print_error(NULL, NULL, 24, NULL);
		return (24);
	}
	err = execute_recursive(tree, split, envl);
	while (wait(&status) > 0)
		;
	free_tree(tree);
	if (status)
		err = status / 256;
	print_child_end(err);
	return (err);
}
