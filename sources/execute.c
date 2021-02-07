/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:37:45 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/07 16:08:50 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_in_out(t_tree *tree)
{
	tree->info->input = 0;
	tree->info->output = 1;
	tree->info->inpipe = -1;
	tree->info->outpipe = -1;
}

void	execute_recursive(t_tree *tree, t_split *split)
{
	int	pfd[2];
	int	type;

	if (!tree)
		return ;
	type = tree->info->type;
	if (type == CMD)
	{
		ft_printf("leave first word : %s\t", split[tree->info->start]);
		ft_printf("input %d\t", tree->info->input);
		ft_printf("output %d\t", tree->info->output);
		ft_printf("inpipe %d\t", tree->info->inpipe);
		ft_printf("outpipe %d\t", tree->info->outpipe);
		return ;
	}
	if (type == SEMIC)
	{
		reset_in_out(tree->left);
		reset_in_out(tree->right);
		reset_in_out(tree);
	}
	else if (type == LEFT)
	{
		pipe(pfd);
		tree->left->info->input = pfd[0];
		tree->left->info->output = tree->info->output;
		tree->right->info->output = pfd[1];
	}
	else
	{
		pipe(pfd);
		tree->left->info->output = pfd[0];
		tree->left->info->input = tree->info->input;
		tree->right->info->input = pfd[1];
	}
	execute_recursive(tree->left, split);
	execute_recursive(tree->right, split);
	if (type != CMD && type != SEMIC)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
}

void	execute(t_split *split, char **env)
{
	t_tree	*tree;

	(void)env;
	tree = create_tree(split);
	ft_printf("\n--- parcours postfixe de l'arbre ---\n");
	print_tree(tree, split);
	ft_printf("\n--- recursive execution ---\n");
	execute_recursive(tree, split);
}
