/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:04 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/12 17:27:53 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_parsing(int err)
{
	if (err == 0)
		return ;
	if (err == 1)
		ft_printf("Wrong format\n");
	else if (err == 2)
		ft_printf("Allocation issue\n");
}

void	print_parsed_command(t_split *split)
{
	int		i;

	ft_printf("\033[33mPARSING\033[0m\n");
	i = 0;
	while (split[i].str)
	{
		ft_printf("\t[%c] [%s]\n", split[i].quote, split[i].str);
		i++;
	}
	ft_printf("\n");
}
