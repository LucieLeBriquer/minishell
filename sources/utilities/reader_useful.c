/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_useful.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:15:33 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/21 16:15:34 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	should_quit(int size, char *line)
{
	if (size == 0 && g_signal != 3
		&& (!line || ft_strlen(line) == 0 || g_signal == 2))
		return (1);
	return (0);
}
