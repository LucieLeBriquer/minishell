#include "minishell.h"

void	trim_spaces(char *s)
{
	int	l;
	int	i;

	l = ft_strlen(s);
	i = l - 1;
	while (i >= 0 && ft_isspace(s[i]))
	{
		s[i] = '\0';
		i--;
	}
}
