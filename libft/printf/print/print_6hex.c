/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_6hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:51:09 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:09:19 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	print_6hex(t_print param, va_list args)
{
	unsigned int	nb;
	int				size;
	char			*nb_utox;
	char			*to_print;

	nb = (unsigned int)va_arg(args, int);
	nb_utox = ft_utox(nb);
	if (nb == 0 && param.precision == 0)
		nb_utox[0] = '\0';
	size = size_int(param, nb_utox);
	to_print = malloc(size * sizeof(char));
	if (!to_print)
		return (0);
	fill_int(&to_print, nb_utox, param, size);
	free(nb_utox);
	ft_putstr(to_print);
	free(to_print);
	return (size - 1);
}
