#include "minishell.h"

int		new_state(char *s, int i)
{
	char	c;

	c = s[i];
	if ((c == '\'') || (c == '\"'))
		return (1);
	if ((c == '|') || (c == '<') || (c == '|') || 
			(c == '>' && c && s[i + 1] && s[i + 1] != '>'))
		return (3);
	if (c == '>' && c && s[i + 1] && s[i + 1] == '>')
		return (4);
	return (0);
}

int		is_operator(char c)
{
	if ((c == '|') || (c == '<') || (c == '>'))
		return (1);
	return (0);
}

char	find_separator(int i, int l, char *s, t_parse *current)
{
	while (i + 1 < l && ft_isspace(s[i]))
		i++;
	current->state = new_state(s, i);
	if (current->state == 0)
		current->sep = ' ';
	else if (current->state == 4)
		current->sep = 'd';
	else
		current->sep = s[i];
	if (i + 1 != l)
		(current->nb_words)++;
	else
		(current->state) = 2;
	return (i);
}

int		nb_words(char *s, int l)
{
	int		i;
	t_parse	current;

	i = 0;
	current.state = 2;
	current.nb_words = 0;
	while (i < l)
	{
		if (current.state == 2)
			i = find_separator(i, l, s, &current);
		else if (current.state == 0)
		{
			while (i < l && !ft_isspace(s[i]) && !is_operator(s[i]))
				i++;
			if (is_operator(s[i]))
				i--;
			current.state = 2;
		}
		else if ((current.state == 3) || (current.state == 4))
		{
			i -= (current.state == 3);
			current.state = 2;
		}
		else if (current.sep == '\"' && i + 1 < l && s[i] == '\\')
			i++;
		else if (s[i] == current.sep)
			current.state = 2;
		i++;
	}
	if (current.state != 2 && !ft_isspace(s[l - 1]))
		return (-1);
	return (current.nb_words);
}

int		len_of_word(char *s, char *sep, int l)
{
	int		i;
	t_parse	current;

	i = 0;
	i = find_separator(i, l, s, &current);
	*sep = current.sep;
	if (current.state == 0)
	{
		while (i < l && !ft_isspace(s[i]) && !is_operator(s[i]))
			i++;
		return (i);
	}
	if ((current.state == 3) || (current.state == 4))
		return (i + 1 + (current.state == 4));
	i++;
	while (s[i] != current.sep)
	{
		if (current.sep == '\"' && i + 1 < l && s[i] == '\\')
			i++;
		i++;
	}
	return (i + 1);
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

t_split	*parse_quotes(char *command, int *err)
{
	int		l;
	int		words;
	t_split	*split;

	l = ft_strlen(command);
	words = nb_words(command, l);
	*err = 1;
	if (words <= 0)
		return (NULL);
	split = malloc((words + 1) * sizeof(t_split));
	*err = 2;
	if (!split)
		return (NULL);
	fill_words(split, words, command, l);
	split[words].str = NULL;
	return (split);
}

void	print_error_parsing(int err)
{
	if (err == 1)
		ft_printf("Bad quoting\n");
	else if (err == 2)
		ft_printf("Allocation issue\n");
}

void	print_parse_quotes(char *command)
{
	t_split	*split;
	int		err;
	int		i;

	split = parse_quotes(command, &err);
	if (!split)
		return (print_error_parsing(err));
	i = 0;
	while (split[i].str)
	{
		ft_printf("[%s] [%c]\n", split[i].str, split[i].quote);
		i++;
	}
}
