#include "minishell.h"

int	ft_export(t_info *cmd, t_split *split, t_list *envl)
{
	char	*empty;
	t_list	*save;
	t_list	*new;

	(void)cmd;
	(void)split;
	(void)envl;
	save = envl; 
	// si pas d'arguments print dans l'ordre alphabétique
	if (cmd->number <= 1)
		return (0);
	while (envl)
	{
		save = envl;
		if (is_in_env(envl, split[cmd->start + 1].str))
		{
			((t_env *)envl->content)->exported = 1;
			return (0);
		}
		envl = envl->next;
	}
	empty = ft_strjoin(split[cmd->start + 1].str, "=''");
	new = init_entry(empty, 1);
	save->next = new;
	return (0);
}
