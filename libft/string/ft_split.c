/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:16:14 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/05 21:09:50 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

static int	nb_wrds(const char *s, const char *set, int *i, int *j)
{
	int	k;
	int	n;

	k = 0;
	n = 0;
	*i = -1;
	*j = 0;
	while (s[k])
	{
		while (s[k] && ft_issep(s[k], set))
			k++;
		if (s[k] && !ft_issep(s[k], set))
			n++;
		while (s[k] && !ft_issep(s[k], set))
			k++;
	}
	return (n);
}

static int	wrd_len(const char *s, const char *set)
{
	int	i;

	i = 0;
	while (s[i] && !ft_issep(s[i], set))
		i++;
	return (i);
}

static char	**ft_free(char **strs, int i)
{
	int		j;

	j = -1;
	while (++j < i)
		free(strs[j]);
	free(strs);
	return (NULL);
}

char	**ft_split(const char *s, const char *set)
{
	char	**strs;
	int		wrds;
	int		i;
	int		j;
	int		len;

	if (!s || !set)
		return (NULL);
	wrds = nb_wrds(s, set, &i, &j);
	strs = malloc(sizeof(char *) * (wrds + 1));
	if (!strs)
		return (NULL);
	strs[wrds] = 0;
	while (++i < wrds)
	{
		while (s[j] && ft_issep(s[j], set))
			j++;
		len = wrd_len(s + j, set);
		strs[i] = malloc(sizeof(char *) * (len + 1));
		if (!(strs[i]))
			return (ft_free(strs, i));
		(void)ft_strlcpy(strs[i], s + j, len + 1);
		j += len;
	}
	return (strs);
}
