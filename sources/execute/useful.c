#include "minishell.h"

int		number_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	free_tab(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int		authorized_char(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && (s[0] != '_'))
		return (0);
	while (s[i] && (s[i] != '='))
	{
		if (!ft_isalnum(s[i]) && (s[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

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
		{
			args[i] = split[cmd->start + j].str;
			i++;
		}
		j++;
	}
	args[i] = NULL;
	return (args);
}

int		is_path(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
