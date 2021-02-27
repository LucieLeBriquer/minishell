#include "minishell.h"

void	change_stdin_stdout(t_info *cmd)
{
	if (cmd->output != 1)
	{
		close(1);
		dup2(cmd->output, 1);
	}
	if (cmd->input != 0)
	{
		close(0);
		dup2(cmd->input, 0);
	}
}

char	*join_all_arguments(t_split *split, int start, int number)
{
	int		i;
	char	*join;
	char	*last;
	char	*empty;

	i = 2;
	if (!split[start + i].str)
	{
		empty = malloc(sizeof(char));
		if (!empty)
			return (NULL);
		empty[0] = '\0';
		return (empty); 
	}
	join = ft_strdup(split[start + i].str);
	while (++i < number)
	{
		last = join;
		join = ft_strjoin(last, split[start + i].str);
		free(last);
		if (split[start + i].space)
			return (join);
		i++;
	}
	return (join);
}
