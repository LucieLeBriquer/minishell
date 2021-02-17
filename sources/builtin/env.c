#include "minishell.h"

static void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

int			ft_env(t_info *cmd, t_split *split, char **env)
{
	int		pid;
	int		status;
	char	**args;

	if (cmd->number > 1)
	{
		args = create_tab_args(cmd, split);
		ft_printf("env: '%s': %s\n", args[1], strerror(2));
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_env(env);
		exit(0);
	}
	else
	{
		wait(&status);
		close_unused_fd(cmd);
		print_child_end(status);
	}
	return (0);
}
