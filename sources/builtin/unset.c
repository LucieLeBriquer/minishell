#include "minishell.h"

void	print_one(t_list *envl, char *pos)
{
	if (envl)
		ft_printf("%s %p [%s]\n", pos, envl, ((t_env *)envl->content)->var);
	else
		ft_printf("%s %p\n", pos, envl);
}

void	unset_one(char *to_unset, t_list *envl)
{
	t_list	*previous;

	previous = envl;
	envl = envl->next;
	while (envl)
	{
		if (variable_match(envl, to_unset))
		{
			previous->next = envl->next;
			free_entry(envl->content);
			free(envl);
			return ;
		}
		previous = envl;
		envl = envl->next;
	}
}

int	ft_unset(t_info *cmd, t_split *split, t_list **envl)
{
	int		i;
	char	**args;

	if (cmd->number <= 1)
		return (0);
	args = create_tab_args(cmd, split);
	i = 1;
	while (args[i])
	{
		if (authorized_char(args[i]))
			unset_one(args[i], *envl);
		i++;
	}
	free(args);
	return (0);
}
