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
	res->exported = ventry->exported;
	return (res);
}

static int	cmp_entry(void *data1, void *data2)
{
	char	*str1;
	char	*str2;

	str1 = ((t_env *)data1)->var;
	str2 = ((t_env *)data2)->var;
	return (ft_strcmp(str1, str2));
}

int			print_sorted(t_list *envl, t_info *cmd)
{
	t_list	*sorted;
	char	**env;
	int		pid;
	int		status;

	sorted = ft_lstmap(envl, &copy_entry, &free_entry);
	ft_lstsort(&sorted, &cmp_entry);
	env = create_env_tab(sorted, 1);
	pid = fork();
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_env(env, 1);
	}
	else
	{
		wait(&status);
		close_unused_fd(cmd);
		print_child_end(status);
	}
	free(env);
	ft_lstclear(&sorted, &free_entry);
	return (0);
}
