/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:23:15 by lle-briq          #+#    #+#             */
/*   Updated: 2020/11/16 17:29:47 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)src;
	if (!dst)
		return (0);
	while (str[i] && i + 1 < size)
	{
		dst[i] = str[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	while (str[i])
		i++;
	return (i);
}
