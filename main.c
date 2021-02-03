#include "minishell.h"

void	prompt(char *cwd)
{
	ft_printf("\033[36m%s@%s \033[37m%s\033[0m$ ", "mini", "shell", cwd);
}

void	print_env_entry(void *ventry)
{
	t_env	*entry;
		
	entry = ventry;
	ft_printf("%s : %s\n", entry->name, entry->value);
}

void	print_entry(t_env *content)
{
	ft_printf("%s : %s\n", content->name, content->value);
}

int		main(int argc, char **argv, char **env)
{
	char	cwd[SIZE_PATH];
	char	*line;
	t_list	*env_list;

	(void)argc;
	(void)argv;
	parse_env(&env_list, env);
	ft_lstiter(env_list, print_env_entry);
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
