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
		if (variable_match(envl, to_export, 1))
		{
			((t_env *)envl->content)->exported = 2;
			if (ft_strchr(to_export, '='))
			{
				if (((t_env *)envl->content)->value)
					free(((t_env *)envl->content)->value);
				((t_env *)envl->content)->value = ft_strdup(ft_strchr(to_export, '=') + 1);
			}
			return ;
		}
		envl = envl->next;
	}
	empty = ft_strdup(to_export);
	new = init_entry(empty, 1);
	if (((t_env *)new->content)->value != NULL)
		((t_env *)new->content)->exported = 2;
	free(empty);
	save->next = new;
}

int		ft_export(t_info *cmd, t_split *split, t_list **envl)
{
	int		i;
	char	**args;
	int		ret;

	args = create_tab_args(cmd, split);
	if (number_of_args(args) <= 1)
	{
		free(args);
		return (print_sorted(*envl, cmd));
	}
	i = 1;
	ret = 0;
	while (args[i])
	{
		if (authorized_char(args[i]))
			export_one(args[i], *envl);
		else
		{
			ft_printf_fd(2, "minishell: export: '%s': not a valid identifier\n", args[i]);
			ret = 1;
		}
		i++;
	}
	free(args);
	return (ret);
}
