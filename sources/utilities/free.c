/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:58:52 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/20 11:42:27 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_all(char *line, t_split *split)
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

void		free_tab(char **args)
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

void		free_lists(t_list **words, t_list **seps, t_list **spaces)
{
	ft_lstclear(words, &free);
	ft_lstclear(seps, &free);
	ft_lstclear(spaces, &free);
}

static void	free_cmd(t_info *cmd)
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
	if (cmd->args_tmp)
		free_tab(cmd->args_tmp);
	if (cmd->seps_tmp)
		free(cmd->seps_tmp);
	if (cmd->spaces_tmp)
		free(cmd->spaces_tmp);
}

void		free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->info)
	{
		free_cmd(tree->info);
		close_unused_fd(tree->info);
		free(tree->info);
	}
	if (tree)
		free(tree);
}
