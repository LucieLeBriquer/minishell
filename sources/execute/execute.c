/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:20:37 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/21 16:20:39 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	return_value(int status, int err)
{
	int	ret;

	ret = err;
	if (status > 0)
	{
		if (status % 256 == 0)
			ret = status / 256;
		else
			ret = status;
	}
	return (ret);
}

static int	execute_recursive(t_tree *tree, t_split *split, t_list **envl)
{
	int	err;
	int	status;

	if (!tree)
		return (0);
	status = SUCCESS;
	err = execute_recursive(tree->left, split, envl);
	if (tree->info->type == CMD)
	{
		err = execute_cmd(tree->info, split, envl);
		close_unused_fd(tree->info);
		return (err);
	}
	if (tree->info->type == SEMIC)
	{
		while (wait(&status) > 0)
			;
		update_last_arg(envl, tree->info, split);
		update_return(envl, return_value(status, err));
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

	status = SUCCESS;
	remove_last_semic(split);
	tree = create_tree(split, line);
	if (pipe_recursive(tree, split, envl))
	{
		free_tree(tree);
		print_error(NULL, NULL, TOOMANY, NULL);
		return (TOOMANY);
	}
	err = execute_recursive(tree, split, envl);
	if (g_signal != 6)
		g_signal = 5;
	while (wait(&status) > 0)
		;
	free_tree(tree);
	return (return_value(status, err));
}
