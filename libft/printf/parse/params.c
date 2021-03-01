/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:24:44 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 20:33:46 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void		init_param(t_print *param)
{
	param->align = 0;
	param->zero = 0;
	param->field = -1;
	param->precision = -1;
	param->type = -1;
}

const char	*parse_align_zero(t_print *param, const char *str)
{
	while (*str == '-' || *str == '0')
	{
		if (*str == '-')
			param->align = 1;
		else
			param->zero = 1;
		str++;
	}
	return (str);
}

static void	fill_star(t_print *param, int nb)
{
	if (param->precision == 1)
	{
		param->precision = nb;
		if (nb < 0)
			param->precision = -1;
	}
	else
	{
		if (nb < 0)
		{
			param->field = (-1) * nb;
			param->align = 1;
		}
		else
			param->field = nb;
	}
}

const char	*parse_param(t_print *param, const char *str, va_list args)
{
	int		nb;

	param->type = is_type(*str);
	str = parse_align_zero(param, str);
	while (param->type < 0)
	{
		if (*str == '.' && str++)
			param->precision = 1;
		if (*str == '*' && str++)
			nb = va_arg(args, int);
		else
			nb = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
		fill_star(param, nb);
		param->type = is_type(*str);
	}
	return (++str);
}
