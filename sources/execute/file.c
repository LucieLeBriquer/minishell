#include "minishell.h"

static void	join_path(char *to_join, char **file, t_info *cmd, t_split *split)
{
	char	*tmp;

	tmp = ft_strjoin(to_join, "/");
	if (*file)
		free(*file);
	*file = ft_strjoin(tmp, split[cmd->start].str);
	free(tmp);
}

int	open_executable(t_info *cmd, t_split *split, t_list *envl, char **file)
{
	char	**path_list;
	char	*path;
	int		i;
	int		fd;

	path = search("PATH", envl);
	if (!path)
		return (-1);
	path_list = ft_split(path, ":=");
	fd = -1;
	*file = NULL;
	i = 0;
	while (path_list[i] && fd < 0)
	{
		join_path(path_list[i], file, cmd, split);
		fd = open(*file, O_RDONLY);
		i++;
	}
	free_tab(path_list);
	if (fd > 0)
	{
		close(fd);
		return (1);
	}
	return (-1);
}
