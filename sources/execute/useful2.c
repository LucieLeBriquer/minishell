/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:51:26 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/02 20:12:33 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_stdin_stdout(t_info *cmd)
{
	if (cmd->output > 1)
	{
		close(1);
		dup(cmd->output);
	}
	if (cmd->input > 0)
	{
		close(0);
		dup(cmd->input);
	}
}

void	close_unused_fd(t_info *cmd)
{
	if (cmd->input > 0)
		close(cmd->input);
	if (cmd->output > 1)
		close(cmd->output);
}

char	*join_all_arguments(t_split *split, int start, int number)
{
	int		i;
	char	*join;
	char	*last;
	char	*empty;

	i = 2;
	if (!split[start + i].str)
	{
		empty = malloc(sizeof(char));
		if (!empty)
			return (NULL);
		empty[0] = '\0';
		return (empty);
	}
	join = ft_strdup(split[start + i].str);
	while (++i < number)
	{
		last = join;
		join = ft_strjoin(last, split[start + i].str);
		free(last);
		if (split[start + i].space)
			return (join);
		i++;
	}
	return (join);
}
