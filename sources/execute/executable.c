#include "minishell.h"

static int	is_path(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	open_executable(t_info *cmd, t_split *split, char **env, char **file)
{
	int		j;
	int		i;
	char	**path_list;
	char	*tmp;
	int		fd;

	j = is_path(env);
	if (j < 0)
		return (-1);
	path_list = ft_split(env[j], ":=");
	i = 0;
	fd = -1;
	*file = NULL;
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
		return (1);
	return (-1);
}
