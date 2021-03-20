/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:48:38 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/20 10:43:25 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_path(char *to_join, char **file, t_info *cmd)
{
	char	*tmp;

	tmp = ft_strjoin(to_join, "/");
	if (*file)
		free(*file);
	*file = ft_strjoin(tmp, cmd->args[cmd->offset]);
	free(tmp);
}

int			open_executable(t_info *cmd, t_list *envl, char **file)
{
	char	**path_list;
	char	*path;
	int		i;
	int		fd;

	*file = NULL;
	path = search_in_env(envl, "PATH");
	if (!path)
		return (ERROR);
	path_list = ft_split(path, ":=");
	fd = -1;
	i = 0;
	while (path_list[i] && fd < 0)
	{
		join_path(path_list[i], file, cmd);
		fd = open(*file, O_RDONLY);
		i++;
	}
	free_tab(path_list);
	if (fd > 0)
	{
		close(fd);
		return (SUCCESS);
	}
	return (ERROR);
}
