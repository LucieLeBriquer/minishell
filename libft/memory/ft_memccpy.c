/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:14:54 by lle-briq          #+#    #+#             */
/*   Updated: 2020/10/20 10:15:07 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*mem;
	unsigned char	*str;
	size_t			i;

	mem = (unsigned char *)dest;
	str = (unsigned char *)src;
	i = -1;
	while (++i < n)
	{
		mem[i] = str[i];
		if (str[i] == (unsigned char)c)
			return (dest + i + 1);
	}
	return (NULL);
}
