#include "minishell.h"

int	ft_unset(t_info *cmd, t_split *split, t_list *envl)
{
	while (envl)
	{
		if (is_in_env(envl, split[cmd->start + 1].str))
		{
			((t_env *)envl->content)->exported = 0;
			((t_env *)envl->content)->var = ft_strjoin(split[cmd->start].str, "=''");
			return (0);
		}
		envl = envl->next;
	}
	return (0);
}
