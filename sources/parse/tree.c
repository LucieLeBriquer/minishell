/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:57:39 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/12 14:32:30 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_node(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == ';')
		return (SEMIC);
	return (0);
}

void		fill_root(t_tree *tree, t_tree *root)
{
	if (!tree)
		return ;
	tree->info->root = root;
	fill_root(tree->left, root);
	fill_root(tree->right, root);
}

int			previous_end_with_slash(t_split *split, int i)
{
	char	*last;

	if (i > 0)
	{
		last = split[i - 1].str;
		return (last[ft_strlen(last) - 1] == '\\');
	}
	return (0);
}

void		tree_final(t_tree **tree, t_tree *last_node, int i[2], char *line)
{
	if (last_node)
		last_node->right = create_leave(i[1], i[0] - i[1], line);
	if (!(*tree))
		*tree = create_leave(0, i[0], line);
	fill_root(*tree, *tree);
}

t_tree		*create_tree(t_split *split, char *line)
{
	t_tree	*tree;
	t_tree	*last_node;
	t_tree	*new_node;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	new_node = NULL;
	tree = NULL;
	while (split[i[0]].str)
	{
		last_node = new_node;
		if (is_node(split[i[0]].sep) && !previous_end_with_slash(split, i[0]))
		{
			new_node = create_node(i[0], is_node(split[i[0]].sep), i[1], line);
			if (!tree)
				tree = new_node;
			if (last_node)
				last_node->right = new_node;
			i[1] = i[0] + 1;
		}
		i[0]++;
	}
	tree_final(&tree, last_node, i, line);
	return (tree);
}
