/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:04 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/18 15:24:37 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_parsing(t_error error)
{
	if (error.num == SUCCESS)
		return ;
	ft_putstr_fd("minishell: ", STDERR);
	if (error.num == SYNTAX_QUOTES)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR);
	else if (error.num == SYNTAX_REDIR)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR);
		if (error.token == 'd')
			ft_putstr_fd(">>", STDERR);
		else
			ft_putchar_fd(error.token, STDERR);
		ft_putstr_fd("'\n", STDERR);
	}
	else if (error.num == ALLOCATION_FAIL)
		ft_putstr_fd("allocation failed\n", STDERR);
}

void	print_error(char *exe, char *file, int err, char *error)
{
	if (!error)
		ft_putstr_fd("minishell: ", STDERR);
	if (exe)
	{
		ft_putstr_fd(exe, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (file)
	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (error)
		ft_putstr_fd(error, STDERR);
	else
		ft_putstr_fd(strerror(err), STDERR);
	ft_putstr_fd("\n", STDERR);
}

void	invalid_identifier(char *str, char *func, int exported)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (func && exported)
	{
		ft_putstr_fd(func, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	write(STDERR, "`", 1);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
}

int		error_msg(int error, char *info)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (error == ALLOCATION_FAIL)
		ft_putstr_fd("allocation failed\n", STDERR);
	if (error == AMBIGUOUS_REDIR)
	{
		ft_putstr_fd(info, STDERR);
		ft_putstr_fd(": ambiguous redirect\n", STDERR);
	}
	return (ERROR);
}
