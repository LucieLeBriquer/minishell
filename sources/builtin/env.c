#include "minishell.h"

int	ft_env(t_info *cmd, t_split *split, char **env)
{
	int	i;

	(void)split;
	ft_printf("\t> env\n");
//	if (cmd->number > 1)
//	{
//		ft_printf("env: '%s': %s\n", split[cmd->start + 1].str, strerror(2));
//		return (-1);
//	}
	i = 0;
	while (env[i])
	{
		ft_printf_fd(cmd->output, "%s\n", env[i]);
		i++;
	}
	return (0);
}
