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
	while (path_list[i] && fd < 0)
	{
		tmp = ft_strjoin(path_list[i], "/");
		*file = ft_strjoin(tmp, split[cmd->start].str);
		fd = open(*file, O_RDONLY);
		i++;
	}
	if (fd > 0)
		return (fd);
	return (-1);
}
