#include "minishell.h"

int		nb_words(char *s, int l)
{
	int		state;
	int		i;
	int		n;
	char	current_sep;

	i = 0;
	n = 0;
	state = 2;
	while (i < l)
	{
		if (state == 2)
		{
			while (i + 1 < l && ft_isspace(s[i]))
				i++;
			state = ((s[i] == '\'') || (s[i] == '\"'));
			current_sep = s[i];
			if (i + 1 != l)
				n++;
		}
		else if (state == 0)
		{
			while (i < l && !ft_isspace(s[i]))
				i++;
			state = 2;
		}
		else if (current_sep == '\"' && i + 1 < l && s[i] == '\\')
			i++;
		else if (s[i] == current_sep)
			state = 2;
		i++;
	}
	if (state != 2 && !ft_isspace(s[l - 1]))
		return (-1);
	return (n);
}

int		len_of_word(char *s, char *sep, int l)
{
	int		state;
	int		i;
	char	current_sep;

	i = 0;
	state = 2;
	while (i < l)
	{
		if (state == 2)
		{
			while (i + 1 < l && ft_isspace(s[i]))
				i++;
			state = ((s[i] == '\'') || (s[i] == '\"'));
			current_sep = s[i];
			*sep = s[i];
		}
		else if (state == 0)
		{
			while (i < l && !ft_isspace(s[i]))
				i++;
			*sep = ' ';
			return (i);
		}
		else if (current_sep == '\"' && i + 1 < l && s[i] == '\\')
			i++;
		else if (s[i] == current_sep)
			return (i + 1);
		i++;
	}
	return (-1);
}

void	fill_words(t_split *split, int words, char *command, int l)
{
	int		i;
	int		k;
	int		word_len;
	char	sep;

	i = 0;
	k = 0;
	while (i < words)
	{
		word_len = len_of_word(command + k, &sep, l);
		split[i].quote = sep;
		split[i].str = malloc((word_len + 2) * sizeof(char));
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
	fill_words(split, words, command, l);
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
