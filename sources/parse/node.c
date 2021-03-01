#include "minishell.h"

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
	info->args = NULL;
	info->env = NULL;
	info->spaces = NULL;
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
