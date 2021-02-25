#include "minishell.h"

int	update_in_out(t_info *cmd, t_split *split)
{
	int	i;

	i = -1;
	while (++i < cmd->number)
	{
		if (split[cmd->start + i].quote == '<')
		{
			if (++i >= cmd->number || cmd->input != 0)
				return (-1);
			else
				cmd->input = open(split[cmd->start + i].str, O_RDONLY);
		}
		else if (split[cmd->start + i].quote == '>')
		{
			if (++i >= cmd->number || cmd->output != 1)
				return (-1);
			else
				cmd->output = open(split[cmd->start + i].str, O_WRONLY |
								O_CREAT | O_TRUNC, 0666);
		}
		else if (split[cmd->start + i].quote == 'd')
		{
			if (++i >= cmd->number || cmd->output != 1)
				return (-1);
			else
				cmd->output = open(split[cmd->start + i].str, O_WRONLY |
								O_CREAT | O_APPEND, 0666);
		}
	}
	if (cmd->input < 0 || cmd->output < 0)
		return (-2);
	return (0);
}
