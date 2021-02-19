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
