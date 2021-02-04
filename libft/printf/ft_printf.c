/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:04:46 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:05:57 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_print	param;
	int		nb_char;

	if (!is_all_coherent(str))
		return (0);
	va_start(args, str);
	nb_char = 0;
	while (*str)
	{
		if (*str != '%')
			str = print_str_classic(str, &nb_char);
		else
		{
			str++;
			init_param(&param);
			str = parse_param(&param, str, args);
			if (!str)
				return (0);
			print_param(param, args, &nb_char);
		}
	}
	va_end(args);
	return (nb_char);
}
