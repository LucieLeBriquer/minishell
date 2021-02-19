#include "minishell.h"

char	*search_in_env(char **env, char *var)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, size) == 0)
			return (ft_strrchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}
