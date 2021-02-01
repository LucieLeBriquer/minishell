#include "minishell.h"

static void	trim_quotes(char *s)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(s);
	while (i + 2 < l)
	{
		s[i] = s[i + 1];
		i++;
	}
	s[i] = '\0';
}

void		trim_char(char *s, char c)
{
	int	i;
	int	j;
	int	l;
	int	n;

	i = 0;
	l = ft_strlen(s);
	while (i < l && s[i] == c)
		i++;
	j = -1;
	while (i + ++j < l)
		s[j] = s[i + j];
	n = j - 1;
	while (j < l)
	{
		s[j] = '\0';
		j++;
	}
	while (n >= 0 && s[n] == c)
	{
		s[n] = '\0';
		n--;
	}
}

void		trim_useless(t_split split)
{
	if (split.quote == '\'' || split.quote == '\"')
		trim_quotes(split.str);
	else
		trim_char(split.str, split.quote);
}
