#include "minishell.h"

void	print_args(char **args, int option, int i)
{
	while (args[i] && args[i + 1])
	{
		ft_printf("%s ", args[i]);
		i++;
	}
	ft_printf("%s", args[i]);
	if (!option)
		ft_printf("\n");
	exit(0);
}

int		ft_echo(t_info *cmd, t_split *split, char **env)
{
	char	**args;
	int		i;
	int		option;
	int		pid;
	int		status;
	
	(void)env;
	args = create_tab_args(cmd, split);
	option = 0;
	i = 1;
	while (args[i] && (ft_strcmp(args[i], "-n") == 0))
		i++;
	if (i > 1)
		option = 1;
	pid = fork();	
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_args(args, option, i);
	}
	else
	{
		wait(&status);
		close_unused_fd(cmd);
		print_child_end(status);
	}
	return (0);
}
