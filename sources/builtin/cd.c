#include "minishell.h"

char	*get_home(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (ft_split(env[i], "=")[1]);
		i++;
	}
	return ("/");
}

int	ft_cd(t_info *cmd, t_split *split, char **env)
{
	char	**args;
	int		fd;

	args = create_tab_args(cmd, split);
	if (cmd->number > 2)
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
		return (chdir(ft_strjoin("./", args[1])));
	}
	else
		return (chdir(get_home(env)));
}
