#include "minishell.h"

int	ft_pwd(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> pwd\n");
	return (0);
}
