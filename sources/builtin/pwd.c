#include "minishell.h"

int	ft_pwd(t_info *cmd, t_split *split, char **env)
{
	char	cwd[SIZE_PATH];
	int		pid;
	int		status;
	
	(void)split;
	(void)env;
	getcwd(cwd, SIZE_PATH);
	pid = fork();	
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		ft_printf("%s\n", cwd);
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
