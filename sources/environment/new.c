#include "minishell.h"

int		expand_then_add(t_list **words, char *str, char sep, t_list *envl)
{
	if (sep == '\"')
		expand_simple(words, str, envl);
	else
		expand_hard(words, str, envl);
	return (SUCCESS);
}

void	print_word(void *data)
{
	char	*s;

	s = (char *)data;
	ft_printf("%s\n", s);
}

int		new_expand(t_info *cmd, t_list *envl)
{
	int		i;
	t_list	*words;
	t_list	*new;
	char	*str;
	char	sep;

	i = -1;
	words = NULL;
	while (++i < cmd->number)
	{
		str = cmd->split[cmd->start + i].str;
		sep = cmd->split[cmd->start + i].sep;
		if (sep == '\"' || sep == ' ')
			expand_then_add(&words, str, sep, envl);
		else
		{
			new = ft_lstnew(ft_strdup(str));
			ft_lstadd_back(&words, new);
		}
	}
	ft_lstiter(words, &print_word);
	return (SUCCESS);
}
