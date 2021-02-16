#include "minishell.h"

char	**create_tab_args(t_info *cmd, t_split *split)
{
	char	**args;
	char	c;
	int		i;
	int		j;

	args = malloc((cmd->number + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (j < cmd->number)
	{	
		c = split[cmd->start + j].quote;
		if (c == 'd' || c == '>' || c == '<')
			j++;
		else
			args[i] = split[cmd->start + j].str;
		i++;
		j++;
	}
	args[i] = NULL;
	return (args);
}
