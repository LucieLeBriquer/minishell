#include "minishell.h"

char	**create_tab_args(t_info *cmd, t_split *split)
{
	char	**args;
	int		i;

	args = malloc((cmd->number + 1) * sizeof(char *));
	i = -1;
	while (++i < cmd->number)
		args[i] = split[cmd->start + i].str;
	args[i] = NULL;
	return (args);
}
