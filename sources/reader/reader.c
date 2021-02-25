#include "minishell.h"

static char	*join_realloc(char *line, char c, int reset)
{
	char	*new_line;
	int		l;
	int		i;

	if (c == '\n')
		return (line);
	if (reset)
		l = 0;
	else
		l = ft_strlen(line);
	new_line = malloc((l + 2) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = -1;
	while (++i < l)
		new_line[i] = line[i];
	free(line);
	new_line[l] = c;
	new_line[l + 1] = '\0';
	return (new_line);
}

static char	*malloc_empty_string(void)
{
	char	*empty;

	empty = malloc(sizeof(char));
	if (!empty)
		return (empty);
	empty[0] = '\0';
	return (empty);
}

int			reader(char **line)
{
	static char	c;
	static int	size;
	static int	reset;

	if (!line)
		return (-1);
	*line = malloc_empty_string();
	if (!(*line))
		return (-1);
	size = read(0, &c, 1);
	if (size < 0)
		return (-1);
	while (size > 0)
	{
		if (c == '\n')
		{
			if ((*line)[ft_strlen(*line) - 1] == '\\')
				(*line)[ft_strlen(*line) - 1] = '\0';
			else
			{
				reset = 1;
				return (1);
			}
		}
		reset = 0;
		*line = join_realloc(*line, c, reset);
		if (!(*line))
			return (-1);
		size = read(0, &c, 1);
		if (size == 0 && *line && ft_strlen(*line) > 0)
			size = 1;
	}
	return (0);
}
