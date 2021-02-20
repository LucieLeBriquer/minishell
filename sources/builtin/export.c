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
		if (variable_match(envl, to_export))
		{
			((t_env *)envl->content)->exported = 1;
			return ;
		}
		envl = envl->next;
	}
	empty = ft_strjoin(to_export, "=''");
	new = init_entry(empty, 1);
	free(empty);
	save->next = new;
}

int		ft_export(t_info *cmd, t_split *split, t_list *envl)
{
	int		i;
	char	**args;

	if (cmd->number <= 1)
		return (print_sorted(envl));
	args = create_tab_args(cmd, split);
	i = 1;
	while (args[i])
	{
		if (authorized_char(args[i]))
			export_one(args[i], envl);
		i++;
	}
	free(args);
	return (0);
}
