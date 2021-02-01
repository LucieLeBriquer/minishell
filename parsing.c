#include "minishell.h"

int		is_begin_quote(char c, int sep, int *waiting_space)
{
	if (sep == ' ' && ((c == '\'') || (c == '\"')))
	{
		*waiting_space = 0;
		return (1);
	}
	if (*waiting_space == 0 && sep == ' ' && c == ' ')
	{
		*waiting_space = 1;
		return (1);
	}
	return (0);
}

int		is_end_quote(char c, int sep, int *waiting_space)
{
	if ((sep != ' ' && (sep == c)) || (sep == ' ' && *waiting_space))
	{
		*waiting_space = 0;
		return (1);
	}
	return (0);
}

int		nb_words(char *s, int l)
{
	int	n;
	int	i;
	int	sep;
	int	waiting_space;

	i = 0;
	n = 0;
	sep = ' ';
	// replace tous les ' ' par des isspace
	waiting_space = 1;
	while (i < l)
	{
		while (sep == ' ' && waiting_space && i + 1 < l && s[i + 1] == ' ')
			i++;
		if (sep == '\"' && s[i] == '\\')
			i++;
		else if (is_begin_quote(s[i], sep, &waiting_space))
		{
			sep = s[i];
			n++;
		}
		else if (is_end_quote(s[i], sep, &waiting_space))
		{
			/*while (i + 1 < l && s[i + 1] == ' ')
				i++;
			if (s[i + 1] == '\'' || s[i + 1] == '\"')
				sep = s[i + 1];
			else*/
				sep = ' ';
			//i++;
		}
		i++;
	}
	if (sep != ' ')
		return (-1);
	return (n);
}

int		len_of_word(char *s, char *type)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '\'' || s[i] == '\"')
	{
		*type = s[i];
		i++;
	}
	else
		*type = ' ';
	while (s[i])
	{
		if (*type == '\"' && s[i] == '\\')
			i++;
		else if (*type == s[i]) 
			return (i + (*type != ' '));
		i++;
	}
	return (-1);
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
		split[i].str = malloc((word_len + 2) * sizeof(char));
		split[i].quote = type;
		if (!split[i].str)
			return ;	// faire un free all
		ft_strlcpy(split[i].str, command + k, word_len + 1);
		split[i].str[word_len + 1] = '\0';
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
	while (split[i].str && split[i].str[0])
	{
		ft_printf("[%s] [%c]\n", split[i].str, split[i].quote);
		i++;
	}
}
