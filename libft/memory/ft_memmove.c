/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:15:20 by lle-briq          #+#    #+#             */
/*   Updated: 2020/11/16 11:45:31 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*mem;
	unsigned char	*str;
	size_t			i;

	mem = (unsigned char *)dest;
	str = (unsigned char *)src;
	i = -1;
	if (!dest && !src)
		return (0);
	if (mem < str)
	{
		while (++i < n)
			mem[i] = str[i];
	}
	else
	{
		while (++i < n)
			mem[n - i - 1] = str[n - i - 1];
	}
	return (dest);
}
