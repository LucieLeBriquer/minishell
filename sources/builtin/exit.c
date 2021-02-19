#include "minishell.h"

int	ft_exit(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	exit(0);
	return (0);
}
