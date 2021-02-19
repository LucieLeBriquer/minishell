#include "minishell.h"

int	ft_cd(t_info *cmd, t_split *split, t_list *envl)
{
	char	**args;
	int		fd;
	int		err;
	char	*path;

	args = create_tab_args(cmd, split);
	if (number_of_args(args) > 2)
	{
		ft_printf("minishell: '%s': %s\n", "cd", "too many arguments");
		return (-1);
	}
	if (args[1])
	{
		fd = open(args[1], O_RDONLY);
		if (fd < 0)
			return (-2);
		close(fd);
		path = ft_strjoin("./", args[1]);
		err = chdir(path);
		free(args);
		free(path);
		return (err);
	}
	free(args);
	return (chdir(search_in_env(envl, "HOME")));
}
