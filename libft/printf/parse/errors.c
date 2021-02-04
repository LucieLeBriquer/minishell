/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:24:37 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:06:25 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	is_type(char c)
{
	if (c == 'c')
		return (0);
	if (c == 's')
		return (1);
	if (c == 'p')
		return (2);
	if (c == 'd')
		return (3);
	if (c == 'i')
		return (4);
	if (c == 'u')
		return (5);
	if (c == 'x')
		return (6);
	if (c == 'X')
		return (7);
	if (c == '%')
		return (8);
	if (c == 'o')
		return (9);
	return (-1);
}

const char	*is_coherent(const char *str)
{
	while (*str == '-' || *str == '0')
		str++;
	if (*str == '*')
		str++;
	else
	{
		while (*str && ft_isdigit(*str))
			str++;
	}
	if (*str == '.')
		str++;
	if (*str == '*')
		str++;
	else
	{
		while (*str && ft_isdigit(*str))
			str++;
	}
	return (str);
}

int	is_all_coherent(const char *str)
{
	int		type;

	while (*str)
	{
		if (*str != '%')
			str++;
		else
		{
			str++;
			str = is_coherent(str);
			type = is_type(*str);
			if (type < 0)
				return (0);
			if (type == 8)
				str++;
		}
	}
	return (1);
}
