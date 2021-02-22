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
	char	*env_var;

	env_var = ((t_env *)envl->content)->var;
	if (ft_strcmp(env_var, var) == 0)
		return (1);
	return (0);
}

char	*ft_strcut(char *line, char c)
{
	int		i;
	char	*res;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	res = malloc((i + 1) * sizeof(char));
	i = 0;
	while (line[i] && line[i] != c)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
