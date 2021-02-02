/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:08:17 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/02 16:20:53 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_split(t_split *split, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(split[j].str);
	free(split);
	return (-1);
}

static int	fill_words(t_split *split, int words, char *command, int l)
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
			return (free_split(split, i));
		ft_strlcpy(split[i].str, command + k, word_len + 1);
		split[i].str[word_len + 1] = '\0';
		trim_useless(split[i]);
		k += word_len;
		i++;
	}
	return (0);
}

t_split		*parse_quotes(char *command, int *err)
{
	int		l;
	int		words;
	t_split	*split;

	trim_spaces_right(command);
	l = ft_strlen(command);
	words = nb_words(command, l);
	*err = 1;
	if (words <= 0)
		return (NULL);
	split = malloc((words + 1) * sizeof(t_split));
	*err = 2;
	if (!split)
		return (NULL);
	if (fill_words(split, words, command, l) < 0)
		return (NULL);
	split[words].str = NULL;
	return (split);
}

void		print_error_parsing(int err)
{
	if (err == 1)
		ft_printf("Wrong format\n");
	else if (err == 2)
		ft_printf("Allocation issue\n");
}

void		print_parse_quotes(char *command)
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
		ft_printf("[%c] [%s]\n", split[i].quote, split[i].str);
		free(split[i].str);
		i++;
	}
	free(split);
}
