#include "minishell.h"

static void	print_args(char **args, int *spaces, int option, int i)
{
	while (args[i] && args[i + 1])
	{
		ft_printf("%s", args[i]);
		if (spaces[i] == 1)
			ft_printf(" ");
		i++;
	}
	if (args[i])
		ft_printf("%s", args[i]);
	if (!option)
		ft_printf("\n");
	exit(0);
}

static int	option_echo(char ***args, int **spaces, t_info *cmd, t_split *split)
{
	int	i;

	i = 1;
	*args = create_tab_args(cmd, split);
	if (!args)
		return (-1);
	*spaces = create_tab_spaces(cmd, split);
	if (!spaces)
	{
		free(args);
		return (-1);
	}
	while ((*args)[i] && (ft_strcmp((*args)[i], "-n") == 0))
		i++;
	return (i);
}

static void	wait_builtin(t_info *cmd)
{
	int	status;

	wait(&status);
	close_unused_fd(cmd);
	print_child_end(status);
}

int	ft_echo(t_info *cmd, t_split *split, t_list **envl)
{
	char	**args;
	int		*spaces;
	int		i;
	int		pid;

	(void)envl;
	i = option_echo(&args, &spaces, cmd, split);
	if (i < 0)
		return (ALLOCATION_FAIL);
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_args(args, spaces, (i > 1), i);
	}
	else
		wait_builtin(cmd);
	free(args);
	free(spaces);
	return (0);
}
