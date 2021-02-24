#include "minishell.h"

int	open_executable(t_info *cmd, t_split *split, t_list *envl, char **file)
{
	char	**path_list;
	char	*path;
	int		i;
	char	*tmp;
	int		fd;
	
	path = search("PATH", envl);
	path_list = ft_split(path, ":=");
	fd = -1;
	*file = NULL;
	i = 0;
	while (path_list[i] && fd < 0)
	{
		tmp = ft_strjoin(path_list[i], "/");
		if (*file)
			free(*file);
		*file = ft_strjoin(tmp, split[cmd->start].str);
		free(tmp);
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
