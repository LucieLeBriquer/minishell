#include "minishell.h"

int	ft_unset(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> unset\n");
	return (0);
}
