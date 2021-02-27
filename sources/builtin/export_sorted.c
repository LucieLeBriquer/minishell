#include "minishell.h"

static void	*copy_entry(void *entry)
{
	t_env	*ventry;
	t_env	*res;

	ventry = (t_env *)entry;
	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->var = ft_strdup(ventry->var);
	res->value = NULL;
	if (ventry->value)
		res->value = ft_strdup(ventry->value);
	res->exported = ventry->exported;
	return (res);
}

static int	cmp_entry(void *data1, void *data2)
{
	char	*str1;
	char	*str2;

	str1 = ((t_env *)data1)->var;
	str2 = ((t_env *)data2)->var;
	return (0);
}

int	print_sorted(t_list *envl, t_info *cmd)
{
	t_list	*sorted;
	int		pid;

	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		sorted = ft_lstmap(envl, &copy_entry, &free_entry);
		ft_lstsort(&sorted, &cmp_entry);
		print_envl(sorted, 1);
		ft_lstclear(&sorted, &free_entry);
		exit(0);
	}
	return (0);
}
