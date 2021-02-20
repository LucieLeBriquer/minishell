#include "minishell.h"

void	*copy_entry(void *entry)
{
	t_env	*ventry;
	t_env	*res;

	ventry = (t_env *)entry;
	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->var = ft_strdup(ventry->var);
	res->exported = ventry->exported;
	return (res);
}

int		cmp_entry(void *data1, void *data2)
{
	char	*str1;
	char	*str2;

	str1 = ((t_env *)data1)->var;
	str2 = ((t_env *)data2)->var;
	return (ft_strcmp(str1, str2));
}

int		print_sorted(t_list *envl)
{
	t_list	*sorted;
	char	**env;

	sorted = ft_lstmap(envl, &copy_entry, &free_entry);
	ft_lstsort(&sorted, &cmp_entry);
	env = create_env_tab(sorted, 1);
	print_env(env);
	free(env);
	ft_lstclear(&sorted, &free_entry);
	return (0);
}

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
