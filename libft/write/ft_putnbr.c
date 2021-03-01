/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:10:12 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 20:33:00 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

static void	rec_putnbr(unsigned int nb, int sg)
{
	if (nb == 0)
	{
		if (sg == -1)
			ft_putchar('-');
		return ;
	}
	rec_putnbr(nb / 10, sg);
	ft_putchar(nb % 10 + '0');
}

void		ft_putnbr(int n)
{
	short int		sg;

	sg = 1 - 2 * (n < 0);
	if (n == 0)
		ft_putchar('0');
	else
		rec_putnbr(sg * n, sg);
}
