#include "minishell.h"

void	prompt(char *cwd)
{
	ft_printf("\033[36m%s@%s \033[34m%s\033[0m$ ", "mini", "shell", cwd);
}

int		main(int argc, char **argv, char **env)
{
	char	cwd[SIZE_PATH];
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	getcwd(cwd, SIZE_PATH);
	prompt(cwd);
	while (get_next_line(0, &line) > 0)
	{
		print_parse_quotes(line);
		free(line);
		prompt(cwd);
	}
	free(line);
	return (0);
}
