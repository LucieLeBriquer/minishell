/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:58:52 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/12 15:07:06 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char *line, t_split *split)
{
	int	i;

	(void)line;
	if (line)
		free(line);
	if (!split)
		return ;
	i = 0;
	while (split[i].str)
	{
		free(split[i].str);
		i++;
	}
	free(split);
}

void	free_tab(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_tree(t_tree *tree)
{
	t_info	*cmd;

	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	cmd = tree->info;
	if (cmd)
	{
		if (cmd->args)
			free_tab(cmd->args);
		if (cmd->argv)
			free(cmd->argv);
		if (cmd->env)
			free_tab(cmd->env);
		if (cmd->seps)
			free(cmd->seps);
		if (cmd->spaces)
			free(cmd->spaces);
		close_unused_fd(cmd);
		free(cmd);
	}
	if (tree)
		free(tree);
}
