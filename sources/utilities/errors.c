/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:04 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/12 14:48:46 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_parsing(t_error error)
{
	if (error.num == SUCCESS)
		return ;
	ft_putstr_fd("minishell: ", 2);
	if (error.num == SYNTAX_QUOTES)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (error.num == SYNTAX_REDIR)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		if (error.token == 'd')
			ft_putstr_fd(">>", 2);
		else
			ft_putchar_fd(error.token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (error.num == ALLOCATION_FAIL)
		ft_putstr_fd("allocation failed\n", 2);
}

void	print_error(char *file, int err, char *error)
{
	if (!error)
		ft_putstr_fd("minishell: ", 2);
	if (file)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
		ft_putstr_fd(error, 2);
	else
		ft_putstr_fd(strerror(err), 2);
	ft_putstr_fd("\n", 2);
}
