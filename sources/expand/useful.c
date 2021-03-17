#include "minishell.h"

int		is_redir(char c)
{
	if (c == '>' || c == 'd' || c == '<')
		return (1);
	return (0);
}

t_list	*new_entry(char *str, char sep, int space)
{
	t_split	*content;

	content = malloc(sizeof(t_split));
	content->str = ft_strdup(str);
	content->sep = sep;
	content->space = space;
	return (ft_lstnew(content));
}

void	free_expd(void *expd)
{
	t_split	*to_free;

	to_free = (t_split *)expd;
	if (to_free)
	{
		free(to_free->str);
		free(to_free);
	}
}
