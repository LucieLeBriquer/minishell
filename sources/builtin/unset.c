#include "minishell.h"

void	unset_one(char *to_unset, t_list *envl)
{
	t_list	*previous;

	previous = envl;
	envl = envl->next;
	while (envl)
	{
		if (variable_match(envl, to_unset, 0))
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
	int		ret;

	if (cmd->number <= 1)
		return (0);
	args = create_tab_args(cmd, split);
	i = 1;
	ret = 0;
	while (args[i])
	{
		if (authorized_char(args[i]) && !ft_strchr(args[i], '='))
			unset_one(args[i], *envl);
		else
		{
			ft_printf_fd(2, "minishell: unset: '%s': not a valid identifier\n", args[i]);
			ret = 1;
		}
		i++;
	}
	free(args);
	return (ret);
}
