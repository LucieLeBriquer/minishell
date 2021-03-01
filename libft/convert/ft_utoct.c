/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:14:48 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 20:30:42 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

static int	itoa_size(unsigned int nb, short int sg, unsigned int base)
{
	if (nb < base)
		return (1 + (sg == -1));
	return (1 + itoa_size(nb / base, sg, base));
}

char		*ft_utoct(unsigned int n)
{
	char	*res;
	char	*base;
	int		i;
	int		l;

	l = itoa_size(n, 1, 8);
	base = "01234567";
	res = malloc(sizeof(char) * (l + 1));
	if (!res)
		return (NULL);
	res[l] = '\0';
	if (n == 0)
		res[0] = '0';
	i = l - 1;
	while (i >= 0)
	{
		res[i] = base[n % 8];
		n = n / 8;
		i--;
	}
	return (res);
}
