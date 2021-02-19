#include "minishell.h"

void	export_one(char *to_export, t_list *envl)
{
	char	*empty;
	t_list	*save;
	t_list	*new;
	
	save = envl; 
	while (envl)
	{
		save = envl;
		if (is_in_env(envl, to_export))
		{
			((t_env *)envl->content)->exported = 1;
			return ;
		}
		envl = envl->next;
	}
	empty = ft_strjoin(to_export, "=''");
	new = init_entry(empty, 1);
	save->next = new;
}

int	ft_export(t_info *cmd, t_split *split, t_list *envl)
{
	int		i;
	char	**args;

	// si pas d'arguments print dans l'ordre alphabétique
	if (cmd->number <= 1)
		return (0);
	args = create_tab_args(cmd, split);
	i = 1;
	while (args[i])
	{
		export_one(args[i], envl);
		i++;
	}
	free(args);
	return (0);
}
