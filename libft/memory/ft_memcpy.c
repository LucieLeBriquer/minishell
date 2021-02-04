/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:14:32 by lle-briq          #+#    #+#             */
/*   Updated: 2020/11/16 11:44:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*mem;
	unsigned char	*str;
	size_t			i;

	if (dest == 0 && src == 0)
		return (0);
	mem = (unsigned char *)dest;
	str = (unsigned char *)src;
	i = -1;
	while (++i < n)
		mem[i] = str[i];
	return (dest);
}
