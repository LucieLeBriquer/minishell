/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:04 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/03 11:39:05 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_parsing(int err)
{
	if (err == 1)
		ft_printf("Wrong format\n");
	else if (err == 2)
		ft_printf("Allocation issue\n");
}

void	print_parsed_command(t_split *split)
{
	int		i;

	i = 0;
	while (split[i].str)
	{
		ft_printf("[%c] [%s]\n", split[i].quote, split[i].str);
		free(split[i].str);
		i++;
	}
}
