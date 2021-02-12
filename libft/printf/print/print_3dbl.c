/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3dbl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:51:09 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/11 17:41:10 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	print_3dbl(t_print param, va_list args)
{
	int		nb;
	int		size;
	char	*nb_itoa;
	char	*to_print;

	nb = va_arg(args, int);
	nb_itoa = ft_itoa(nb);
	if (nb == 0 && param.precision == 0)
		nb_itoa[0] = '\0';
	size = size_int(param, nb_itoa);
	to_print = malloc(size * sizeof(char));
	if (!to_print)
		return (0);
	fill_int(&to_print, nb_itoa, param, size);
	free(nb_itoa);
	ft_putstr_fd(to_print, param.fd);
	free(to_print);
	return (size - 1);
}
