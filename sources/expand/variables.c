#include "minishell.h"

int		count_var(t_info cmd)
{
	int	nb_var;
	int	i;

	nb_var = 0;
	i = 0;
	while (++i < cmd.nb_args)
	{
		while (i < cmd.nb_args && cmd.spaces[i] == 0)
			i++;
		nb_var++;
	}
	return (nb_var);
}

void	print_tab_var(char **var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		ft_printf("[%s]\n", var[i]);
		i++;
	}
}

static void	fill_vars(t_info cmd, int nb_var, char **vars)
{
	int		i;
	int		j;
	int		end;
	char	*current;
	char	*tmp;

	i = -1;
	j = 1;
	while (++i < nb_var)
	{
		end = 0;
		current = ft_strdup("");
		while (j < cmd.number && !end)
		{
			tmp = current;
			current = ft_strjoin(tmp, cmd.args[j]);
			free(tmp);
			if (cmd.spaces[j])
				end = 1;
			j++;
		}
		vars[i] = ft_strdup(current);
		free(current);
	}
	vars[nb_var] = NULL;
}

int		multiple_var(t_info cmd, t_list **envl)
{
	int		nb_var;
	char	**vars;
	int		err;

	(void)envl;
	nb_var = count_var(cmd);
	vars = malloc((nb_var + 1) * sizeof(char *));
	if (!vars)
		return (-1);
	fill_vars(cmd, nb_var, vars);
	print_tab_var(vars);
	err = export_all(vars, envl);
	free_tab(vars);
	return (err);
}
