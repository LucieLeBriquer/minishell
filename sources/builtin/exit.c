#include "minishell.h"

int	ft_exit(t_info *cmd, t_split *split, t_list **envl)
{
	ft_printf("exit\n");
	free_all(cmd->line, split);
	ft_lstclear(envl, &free_entry);
	exit(0);
	return (0);
}
