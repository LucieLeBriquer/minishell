#include "minishell.h"

int		is_cmd(char *s)
{
	int	i;

	i = 0;
	while (i < NB_CMD)
	{
		if (ft_strcmp(s, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	char	*command = argv[1];
	char	**words;
	int		i;

	words = ft_split(command, " ");
	i = 0;
	while (words[i])
	{
		if (is_cmd(words[i]))
			ft_printf("CMD");
		ft_printf("[%s]\n", words[i]);
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}
