#include "minishell.h"

int		nb_words(char *s, int l)
{
	int	n;
	int	i;
	int	type_quotes;

	i = 0;
	n = 0;
	type_quotes = -1;
	while (i < l)
	{
		if (type_quotes == 0 && s[i] == '\\')
			i++;
		else if ((type_quotes == 0 && s[i] == '\"') 
			|| (type_quotes == 1 && s[i] == '\''))
			type_quotes = -1;
		else if ((type_quotes == -1 && s[i] == '\'') 
			|| (type_quotes == -1 && s[i] == '\"'))
		{
			n++;
			type_quotes = (s[i] == '\'');
		}
		i++;
	}
	if (type_quotes != -1)
		return (-1);
	return (n + 1);
}

int		len_of_word(char *s, char *type)
{
	int	i;
	int	type_quotes;

	i = 0;
	if (s[i] == '\'' || s[i] == '\"')
	{
		type_quotes = (s[i] == '\'');
		i++;
	}
	else
		type_quotes = -1;
	*type = ' ';
	while (s[i])
	{
		if (type_quotes == 0 && s[i] == '\\')
			i++;
		else if ((type_quotes == 0 && s[i] == '\"') 
			|| (type_quotes == 1 && s[i] == '\''))
		{
			*type = s[i];
			type_quotes = -1;
			return (i + 1);
		}
		else if ((type_quotes == -1 && s[i] == '\'') 
			|| (type_quotes == -1 && s[i] == '\"'))
			return (i);
		i++;
	}
	*type = ' ';
	return (i);
}

void	fill_words(t_split *split, int words, char *command)
{
	int		i;
	int		k;
	int		word_len;
	char	type;

	i = 0;
	k = 0;
	while (i < words)
	{
		while (command[k] == ' ')
			k++;
		word_len = len_of_word(command + k, &type);
		split[i].str = malloc((word_len + 1) * sizeof(char));
		split[i].quote = type;
		if (!split[i].str)
			return ;	// faire un free all
		ft_strlcpy(split[i].str, command + k, word_len + 1);
		trim_useless(split[i]);
		k += word_len;
		i++;
	}
}

t_split	*parse_quotes(char *command)
{
	int		l;
	int		words;
	t_split	*split;

	l = ft_strlen(command);
	words = nb_words(command, l);
	if (words <= 0)
		ft_printf("Bad quoting\n");
	split = malloc((words + 1) * sizeof(t_split));
	if (!split)
		return (NULL);
	fill_words(split, words, command);
	split[words].str = NULL;
	return (split);
}

void	print_parse_quotes(char *command)
{
	t_split	*split;
	int		i;

	split = parse_quotes(command);
	i = 0;
	while (split[i].str)
	{
		ft_printf("[%s] [%c]\n", split[i].str, split[i].quote);
		i++;
	}
}
