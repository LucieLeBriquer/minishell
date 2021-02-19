#include "minishell.h"

int	ft_exit(t_info *cmd, t_split *split, t_list *envl)
{
	(void)cmd;
	(void)split;
	(void)envl;
	exit(0);
	return (0);
}
