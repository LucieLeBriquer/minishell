#include "minishell.h"

static void	wait_father(char **args, t_info *cmd)
{
	int		status;

	wait(&status);
	free_tab(args);
	close_unused_fd(cmd);
	print_child_end(status);
}

int	fork_and_exec(t_info *cmd, t_split *split, t_list *envl, char *file)
{
	char	**args;
	char	**env;
	int		ret;
	int		pid;

	env = create_env_tab(envl, 0);
	args = NULL;
	ret = -1;
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		args = create_tab_args(cmd, split);
		if (file)
			ret = execve(file, args, env);
		else
			ret = execve(split[cmd->start].str, args, env);
	}
	else
		wait_father(args, cmd);
	free_tab(env);
	return (ret);
}
