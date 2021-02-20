#include "minishell.h"

void	unset_one(char *to_unset, t_list *envl)
{
	while (envl)
	{
		if (is_in_env(envl, to_unset))
		{
			((t_env *)envl->content)->exported = 0;
			((t_env *)envl->content)->var = ft_strjoin(to_unset, "=''");
			free(to_unset);
			return ;
		}
		envl = envl->next;
	}
}

int	ft_unset(t_info *cmd, t_split *split, t_list *envl)
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
			unset_one(args[i], envl);
		i++;
	}
	free(args);
	return (0);
}
