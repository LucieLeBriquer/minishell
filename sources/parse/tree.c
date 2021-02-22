#include "minishell.h"

static int	is_operator(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == ';')
		return (SEMIC);
	return (0);
}

t_info	*init_node(int i, int type, int number, char *line)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->type = type;
	info->input = 0;
	info->output = 1;
	info->output = 1;
	info->start = i;
	info->line = line;
	info->number = number;
	return (info);
}

t_tree	*create_leave(int start, int number, char *line)
{
	t_tree	*new;
	t_info	*new_info;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new_info = init_node(start, 0, number, line);
	new->left = NULL;
	new->right = NULL;
	new->info = new_info;
	return (new);
}

t_tree	*create_node(int i, int type, int start, char *line)
{
	t_tree		*new;
	t_info		*new_info;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new_info = init_node(i, type, 1, line);
	new->left = create_leave(start, i - start, line);
	new->right = NULL;
	new->info = new_info;
	return (new);
}

void	fill_root(t_tree *tree, t_tree *root)
{
	if (!tree)
		return ;
	tree->info->root = root;
	fill_root(tree->left, root);
	fill_root(tree->right, root);
}

int		previous_end_with_slash(t_split *split, int i)
{
	char	*last;

	if (i > 0)
	{
		last = split[i - 1].str;
		return (last[ft_strlen(last) - 1] == '\\');
	}
	return (0);
}
t_tree	*create_tree(t_split *split, char *line)
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
		if (type && !previous_end_with_slash(split, i))
		{
			new_node = create_node(i, type, j, line);
			if (j == 0)
				tree = new_node;
			if (last_node)
				last_node->right = new_node;
			j = i + 1;
		}
		i++;
	}
	if (last_node)
		last_node->right = create_leave(j, i - j, line);
	if (!tree)
		tree = create_leave(0, i, line);
	fill_root(tree, tree);
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
