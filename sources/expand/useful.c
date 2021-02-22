#include "minishell.h"

char	*search_in_env(t_list *envl, char *var)
{
	int	size;

	size = ft_strlen(var);
	while (envl)
	{
		if (ft_strncmp(((t_env *)envl->content)->var, var, size) == 0)
			return (ft_strrchr(((t_env *)envl->content)->var, '=') + 1);
		envl = envl->next;
	}
	return (NULL);
}

int		list_size(t_list *begin_list)
{
	int		i;

	i = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}

void	ft_lstsort(t_list **begin_list, int (*cmp)())
{
	t_list	*current;
	void	*save;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = list_size(*begin_list);
	while (i < size)
	{
		j = 0;
		current = *begin_list;
		while (j < size - 1 - i)
		{
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				save = current->content;
				current->content = current->next->content;
				current->next->content = save;
			}
			current = current->next;
			j++;
		}
		i++;
	}
}


int		variable_match(t_list *envl, char *var)
{
	int		size;
	char	*to_find;
	char	*env_var;
	int		i;

	size = ft_strlen(var);
	to_find = malloc((size + 2) * sizeof(char));
	if (!to_find)
		return (0);
	i = -1;
	while (++i < size && var[i] != '=')
		to_find[i] = var[i];
	to_find[i] = '=';
	to_find[i + 1] = '\0';
	env_var = ((t_env *)envl->content)->var;
	if (ft_strncmp(env_var, to_find, i + 1) == 0 || 
		((ft_strncmp(env_var, to_find, i) == 0) && (env_var[i] == '\0')))
	{
		free(to_find);
		return (1);
	}
	free(to_find);
	return (0);
}
