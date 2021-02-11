#include "minishell.h"

int	ft_exit(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> exit\n");
	return (0);
}
