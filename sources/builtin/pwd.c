#include "minishell.h"

int	ft_pwd(t_info *cmd, t_split *split, t_list **envl)
{
	char	cwd[SIZE_PATH];
	int		pid;

	(void)split;
	(void)envl;
	getcwd(cwd, SIZE_PATH);
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		ft_printf("%s\n", cwd);
		exit(0);
	}
	return (0);
}
