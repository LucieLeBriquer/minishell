#include "minishell.h"

int	ft_export(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> export\n");
	return (0);
}
