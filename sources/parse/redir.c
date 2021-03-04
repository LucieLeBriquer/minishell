/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:39:05 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 14:47:54 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_input(t_info *cmd, int i)
{
	if (++i >= cmd->nb_args)
		return (-1);
	if (cmd->input != 0)
		close(cmd->input);
	errno = 0;
	cmd->input = open(cmd->args[i], O_RDONLY);
	cmd->err = errno;
	cmd->file_error = cmd->args[i];
	if (cmd->input < 0)
		return (-2);
	return (0);
}

static int	fill_out(t_info *cmd, int i)
{
	if (++i >= cmd->nb_args)
		return (-1);
	if (cmd->output != 1)
		close(cmd->output);
	errno = 0;
	cmd->output = open(cmd->args[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	cmd->err = errno;
	cmd->file_error = cmd->args[i];
	if (cmd->output < 0)
		return (-2);
	return (0);
}

static int	fill_app(t_info *cmd, int i)
{
	if (++i >= cmd->nb_args)
		return (-1);
	if (cmd->output != 1)
		close(cmd->output);
	errno = 0;
	cmd->output = open(cmd->args[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
	cmd->err = errno;
	cmd->file_error = cmd->args[i];
	if (cmd->output < 0)
		return (-2);
	return (0);
}

int			update_in_out(t_info *cmd)
{
	int		i;

	i = -1;
	while (++i < cmd->nb_args)
	{
		if (cmd->seps[i] == '<' && fill_input(cmd, i))
			return (-1);
		else if (cmd->seps[i] == '>' && fill_out(cmd, i))
			return (-1);
		else if (cmd->seps[i] == 'd' && fill_app(cmd, i))
			return (-1);
	}
	return (0);
}
