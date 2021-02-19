#include "minishell.h"

int	ft_export(t_info *cmd, t_split *split, t_list *envl)
{
	(void)cmd;
	(void)split;
	(void)envl;
	ft_printf("\t> export\n");
	return (0);
}
