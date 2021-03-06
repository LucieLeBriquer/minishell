/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:41:41 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/18 16:02:17 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_info *cmd, t_list **envl)
{
	char	cwd[SIZE_PATH];
	int		pid;

	(void)envl;
	getcwd(cwd, SIZE_PATH);
	pid = fork();
	if (pid == -1)
		return (error_msg(FORK_FAIL));
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		ft_putstr(cwd);
		ft_putstr("\n");
		exit(SUCCESS);
	}
	return (SUCCESS);
}
