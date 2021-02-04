/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:26:34 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 14:46:01 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (size <= d)
		return (size + s);
	i = d;
	while (i + 1 < size && src[i - d])
	{
		dst[i] = (char)(src[i - d]);
		i++;
	}
	dst[i] = '\0';
	return (s + d);
}
