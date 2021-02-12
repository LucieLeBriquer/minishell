/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_9oct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:51:09 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/11 17:42:29 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	print_9oct(t_print param, va_list args)
{
	unsigned int	nb;
	int				size;
	char			*nb_utoct;
	char			*to_print;

	nb = (unsigned int)va_arg(args, int);
	nb_utoct = ft_utoct(nb);
	if (nb == 0 && param.precision == 0)
		nb_utoct[0] = '\0';
	size = size_int(param, nb_utoct);
	to_print = malloc(size * sizeof(char));
	if (!to_print)
		return (0);
	fill_int(&to_print, nb_utoct, param, size);
	free(nb_utoct);
	ft_putstr_fd(to_print, param.fd);
	free(to_print);
	return (size - 1);
}
