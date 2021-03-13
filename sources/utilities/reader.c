/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:58:29 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/13 18:42:08 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_realloc(char *line, char c, int reset)
{
	char	*new_line;
	int		l;
	int		i;

	if (c == '\n')
		return (line);
	if (reset || g_sigint == 1)
	{
		g_sigint = 2;
		l = 0;
	}
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

static int	ignore_escaped(char c, char **line, int *reset)
{
	if (c == '\n')
	{
		if (ft_strlen(*line) > 0 && (*line)[ft_strlen(*line) - 1] == '\\')
			(*line)[ft_strlen(*line) - 1] = '\0';
		else
		{
			*reset = 1;
			return (1);
		}
	}
	return (0);
}

static int	error_and_first_read(char **line, char *c)
{
	int	size;

	if (!line)
		return (-1);
	*line = malloc_empty_string();
	if (!(*line))
		return (-1);
	size = read(0, c, 1);
	return (size);
}

int			reader(char **line)
{
	static char	c;
	static int	size;
	static int	reset;

	size = error_and_first_read(line, &c);
	if (size < 0)
		return (-1);
	while (size >= 0)
	{
		if (size == 0 && (!(*line) || ft_strlen(*line) == 0))
			break ;
		else if (size == 0)
			size = read(0, &c, 1);
		else
		{
			if (ignore_escaped(c, line, &reset))
				return (1);
			reset = 0;
			*line = join_realloc(*line, c, reset);
			if (!(*line))
				return (-1);
			size = read(0, &c, 1);
		}
	}
	return (0);
}
