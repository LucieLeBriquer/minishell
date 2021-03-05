/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:39:19 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/05 15:49:25 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_info *cmd, t_list **envl)
{
	int		fd;
	int		err;
	char	*path;

	if (number_of_args(cmd->argv) > 2)
	{
		ft_printf("minishell: '%s': %s\n", "cd", "too many arguments");
		return (-1);
	}
	if (cmd->args[1])
	{
		fd = open(cmd->argv[1], O_RDONLY);
		if (fd < 0)
			return (-2);
		close(fd);
		path = ft_strjoin("./", cmd->argv[1]);
		err = chdir(path);
		free(path);
		return (err);
	}
	return (chdir(search_in_env(*envl, "HOME")));
}
