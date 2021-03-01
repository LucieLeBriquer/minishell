/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 22:50:53 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 20:32:33 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	l;
	char	*map;

	i = -1;
	if (!s)
		return (NULL);
	l = ft_strlen(s);
	map = malloc((l + 1) * sizeof(char));
	if (!map)
		return (NULL);
	while (++i < l)
		map[i] = (*f)(i, s[i]);
	map[l] = '\0';
	return (map);
}
