/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:14:48 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/05 21:11:04 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

static int	utoa_size(unsigned int nb)
{
	if (nb < 10)
		return (1);
	return (1 + utoa_size(nb / 10));
}

char	*ft_utoa(unsigned int n)
{
	char			*res;
	int				i;
	int				l;

	l = utoa_size(n);
	res = malloc(sizeof(char) * (l + 1));
	if (!res)
		return (NULL);
	res[l] = '\0';
	if (n == 0)
		res[0] = '0';
	i = l - 1;
	while (i >= 0)
	{
		res[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (res);
}
