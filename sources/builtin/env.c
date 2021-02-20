#include "minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	exit(0);
}

int			ft_env(t_info *cmd, t_split *split, t_list *envl)
{
	int		pid;
	int		status;
	char	**args;
	char	**env;

	args = create_tab_args(cmd, split);
	if (number_of_args(args) > 1)
	{
		ft_printf("env: should be used without options or arguments\n");
		free(args);
		return (-1);
	}
	env = create_env_tab(envl, 1);
	pid = fork();
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_env(env);
	}
	else
	{
		wait(&status);
		close_unused_fd(cmd);
		print_child_end(status);
	}
	free(env);
	return (0);
}
