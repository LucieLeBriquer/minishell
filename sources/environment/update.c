#include "minishell.h"

void	update_return(t_list **envl, int err)
{
	add_env("?begin", ft_itoa(err), envl, -1);
	if (err == 130)
		g_sigint = 0;
}

int		get_return(t_list *envl)
{
	return (ft_atoi(search_in_env(envl, "?begin")));
}

void	update_env(t_list **envl)
{
	char	*pwd;
	char	cwd[SIZE_PATH];

	pwd = search_in_env(*envl, "PWD");
	getcwd(cwd, SIZE_PATH);
	if (ft_strcmp(pwd, cwd) != 0)
	{
		add_env("OLDPWD", ft_strdup(pwd), envl, 1);
		add_env("PWD", ft_strdup(cwd), envl, 1);
	}
}
