#include "minishell.h"

static int	count_arg(t_info cmd, t_split *split)
{
	int	nb_arg;
	int	i;

	nb_arg = 1;
	i = -1;
	while (++i < cmd.number)
	{
		if (split[cmd.start + i].space)
			nb_arg++;
	}
	return (nb_arg);
}

static void	fill_args(t_info cmd, t_split *split)
{
	int		i;
	int		j;
	int		end;
	char	*current;
	char	*tmp;

	i = -1;
	j = 0;
	while (++i < cmd.nb_args)
	{
		end = 0;
		current = ft_strdup("");
		while (j < cmd.number && !end)
		{
			tmp = current;
			current = ft_strjoin(tmp, split[cmd.start + j].str);
			free(tmp);
			if (split[cmd.start + j].space)
				end = 1;
			j++;
		}
		cmd.args[i] = ft_strdup(current);
		free(current);
	}
	cmd.args[i] = NULL;
}

int			join_words(t_info *cmd, t_split *split)
{
	cmd->nb_args = count_arg(*cmd, split);
	cmd->args = malloc((cmd->nb_args + 1) * sizeof(char *));
	if (!(cmd->args))
		return (-1);
	fill_args(*cmd, split);
	return (0);
}
