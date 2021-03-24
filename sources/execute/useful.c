/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:51:26 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/24 14:51:44 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_stdin_stdout(t_info *cmd)
{
	if (cmd->output != STDOUT)
	{
		close(STDOUT);
		dup(cmd->output);
	}
	if (cmd->input != STDIN)
	{
		close(STDIN);
		dup(cmd->input);
	}
}

void	close_unused_fd(t_info *cmd)
{
	if (cmd->input != STDIN && cmd->input != -1)
		close(cmd->input);
	if (cmd->output != STDOUT && cmd->output != -1)
		close(cmd->output);
}

int		authorized_char(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && (s[0] != '_'))
		return (0);
	while (s[i] && (s[i] != '='))
	{
		if (!ft_isalnum(s[i]) && (s[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

int		is_path(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
