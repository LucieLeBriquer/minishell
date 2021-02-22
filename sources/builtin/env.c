#include "minishell.h"

char	*add_quotes(char *str)
{
	int		i;
	int		j;
	char	*res;
	int		first;
	int		size;

	size = ft_strlen(str);
	res = malloc((size + 3) * sizeof(char));
	if (!res)
		return (NULL);
	first = 1;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=' && first)
		{
			first = 0;
			res[j] = str[i];
			res[j + 1] = '\"';
			j++;
		}
		else
			res[j] = str[i];
		j++;
		i++;
	}
	if (j == i)
		res[i] = '\0';
	res[size + 1] = '\"';
	res[size + 2] = '\0';
	return (res);
}

void	print_env(char **env, int declare)
{
	int		i;
	char	*quoted;

	i = 0;
	while (env[i])
	{
		if (declare && ft_strncmp(env[i], "_=", 2) != 0)
		{
			ft_printf("declare -x ");
			quoted = add_quotes(env[i]);
			ft_printf("%s\n", quoted);
			free(quoted);
		}
		else if (!declare)
			ft_printf("%s\n", env[i]);
		i++;
	}
	exit(0);
}

int			ft_env(t_info *cmd, t_split *split, t_list **envl)
{
	int		pid;
	int		status;
	char	**args;
	char	**env;

	args = create_tab_args(cmd, split);
	if (number_of_args(args) > 1)
	{
		ft_printf("env: should be used without option and argument\n");
		free(args);
		return (-1);
	}
	free(args);
	env = create_env_tab(*envl, 2);
	pid = fork();
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_env(env, 0);
	}
	else
	{
		wait(&status);
		close_unused_fd(cmd);
		print_child_end(status);
	}
	free(env);
	return (0);
}
