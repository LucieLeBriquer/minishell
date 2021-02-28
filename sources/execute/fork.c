#include "minishell.h"

int	fork_and_exec(t_info *cmd, t_split *split, t_list *envl, char *file)
{
	int		ret;
	int		pid;

	cmd->env = create_env_tab(envl, 0);
	ret = -1;
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		close_unused_fd(cmd);
		cmd->args = create_tab_args(cmd, split);
		if (file)
			ret = execve(file, cmd->args, cmd->env);
		else
			ret = execve(split[cmd->start].str, cmd->args, cmd->env);
	}
	return (0);
}
