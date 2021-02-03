#include "minishell.h"

char	*search_env(t_list *env, char *to_find)
{
	t_env	*content;

	while (env)
	{
		content = env->content;
		if (ft_strcmp(content->name, to_find) == 0)
			return (content->value);
		env = env->next;
	}
	return (NULL);
}
