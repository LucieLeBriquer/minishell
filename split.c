#include "minishell.h"

void	trim_spaces(char *s)
{
	int	i;
	int	j;
	int	l;
	int	n;

	i = 0;
	l = ft_strlen(s);
	while (i < l && s[i] == ' ')
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
	while (n >= 0 && s[n] == ' ')
	{
		s[n] = '\0';
		n--;
	}
}

char	**ft_specialsplit(char *s)
{
	char	**quotes_split;
	int		size;

	quotes_split = ft_split(s, "\"");
	if (!quotes_split)
		return (NULL);
	size = 0;
	while (quotes_split[size])
	{
		if (size % 2 == 0)
			trim_spaces(quotes_split[size]);
		ft_printf("[%s]\n", quotes_split[size]);
		size++;
	}
	if (size % 2 != 0)
		return (NULL);
	return (quotes_split);
}

int		main(int argc, char **argv)
{
	ft_specialsplit(argv[1]);
	return (0);
}
