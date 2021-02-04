/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:11:19 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/05 21:14:51 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	l;
	size_t	i;
	char	*dup;

	l = ft_strlen(s);
	dup = malloc(sizeof(char) * (l + 1));
	i = -1;
	if (!dup)
		return (NULL);
	while (++i < l)
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}
