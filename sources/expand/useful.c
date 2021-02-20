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

int		variable_match(t_list *envl, char *var)
{
	int		size;
	char	*to_find;
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
	if (ft_strncmp(((t_env *)envl->content)->var, to_find, i + 1) == 0)
	{
		free(to_find);
		return (1);
	}
	free(to_find);
	return (0);
}
