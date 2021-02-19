#include "minishell.h"

int	ft_unset(t_info *cmd, t_split *split, t_list *envl)
{
	(void)cmd;
	(void)split;
	(void)envl;
	ft_printf("\t> unset\n");
	return (0);
}
