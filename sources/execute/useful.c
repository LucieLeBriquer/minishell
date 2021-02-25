#include "minishell.h"

int	number_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	authorized_char(char *s)
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

int	*create_tab_spaces(t_info *cmd, t_split *split)
{
	int		*spaces;
	char	c;
	int		i;
	int		j;

	spaces = malloc((cmd->number + 1) * sizeof(int));
	i = 0;
	j = 0;
	while (j < cmd->number)
	{	
		c = split[cmd->start + j].quote;
		if (c == 'd' || c == '>' || c == '<')
			j++;
		else
		{
			spaces[i] = split[cmd->start + j].space;
			i++;
		}
		j++;
	}
	spaces[i] = -1;
	return (spaces);
}

int	is_path(char *word)
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
