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
}

static int	option_echo(t_info *cmd, t_split *split)
{
	int	i;

	i = 1;
	cmd->args = create_tab_args(cmd, split);
	cmd->spaces = create_tab_spaces(cmd, split);
	if (!cmd->args || !cmd->spaces)
		return (-1);
	while ((cmd->args)[i] && (ft_strcmp((cmd->args)[i], "-n") == 0))
		i++;
	return (i);
}

int	ft_echo(t_info *cmd, t_split *split, t_list **envl)
{
	int		i;
	int		pid;

	(void)envl;
	i = option_echo(cmd, split);
	if (i < 0)
		return (ALLOCATION_FAIL);
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_args(cmd->args, cmd->spaces, (i > 1), i);
		exit(0);
	}
	return (0);
}
