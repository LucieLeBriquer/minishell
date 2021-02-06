#include "minishell.h"

static int	is_operator(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (LEFT);
	if (c == '>')
		return (RIGHT);
	if (c == 'd')
		return (RRIGHT);
	if (c == ';')
		return (SEMIC);
	return (0);
}

t_info	*init_node(int i, int type, int number)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->type = type;
	info->input = 0;
	info->output = 1;
	info->start = i;
	info->number = number;
	return (info);
}

t_tree	*create_leave(int start, int number)
{
	t_tree	*new;
	t_info	*new_info;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new_info = init_node(start, 0, number);
	new->left = NULL;
	new->right = NULL;
	new->info = new_info;
	return (new);
}

t_tree	*create_node(int i, int type, int start)
{
	t_tree	*new;
	t_info	*new_info;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new_info = init_node(i, type, 1);
	new->left = create_leave(start, i - start);
	new->right = NULL;
	new->info = new_info;
	return (new);
}

t_tree	*create_tree(t_split *split)
{
	t_tree	*tree;
	t_tree	*last_node;
	t_tree	*new_node;
	int		type;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_node = NULL;
	tree = NULL;
	while (split[i].str)
	{
		type = is_operator(split[i].quote);
		last_node = new_node;
		if (type)
		{
			new_node = create_node(i, type, j);
			if (j == 0)
				tree = new_node;
			if (last_node)
				last_node->right = new_node;
			j = i + 1;
		}
		i++;
	}
	if (last_node)
		last_node->right = create_leave(j, i - j);
	return (tree);
}

void	print_tree(t_tree *tree, t_split *split)
{
	int	i;

	if (tree == NULL)
		return ;
	print_tree(tree->left, split);
	ft_printf("type : %d\t%d[%d]\t", tree->info->type, tree->info->start, tree->info->number);
	ft_printf("operator : %c\t", split[tree->info->start].quote);
	i = -1;
	while (++i < tree->info->number)
		ft_printf("%s ", split[tree->info->start + i].str);
	ft_printf("\n");
	print_tree(tree->right, split);
}
