#include "minishell.h"

char	*search(char *var, t_list *envl)
{
	while (envl)
	{
		if (ft_strcmp(((t_env *)envl->content)->var, var) == 0)
			return (((t_env *)envl->content)->value);
		envl = envl->next; 
	}
	return (NULL);
}

int		size_var(char *str, t_list *envl, char **value)
{
	char	*var;
	int		size;
	int		i;

	size = ft_strlen(str);
	var = malloc((size + 1) * sizeof(char));
	if (!var)
		return (0);
	i = -1;
	while (++i < size && (ft_isalpha(str[i]) || str[i] == '_'))
		var[i] = str[i];
	var[i] = '\0';
	*value = search(var, envl);
	free(var);
	if (!(*value))
		return (0);
	return (ft_strlen(*value));
}

int		expanded_size(char *str, t_list *envl)
{
	int		i;
	int		res;
	int		l;
	char	*value;

	l = ft_strlen(str);
	res = 0;
	i = 0;
	while (i < l)
	{
		if (str[i] == '$')
		{
			if (i > 0 && str[i - 1] == '\\')
				i++;
			else
			{
				i++;
				res += size_var(str + i, envl, &value);
				while (i < l && (ft_isalpha(str[i]) || str[i] == '_'))
					i++;
			}
		}
		res++;
		i++;
	}
	return (res + 1);
}

void	fill_expanded(char *fill, char *old, t_list *envl)
{
	char	*current_var;
	int		l;
	int		res;
	int		size;
	int		i;

	l = ft_strlen(old);
	res = 0;
	i = 0;
	while (i < l)
	{
		if ((old[i] == '\"' || old[i] == '\\' || old[i] == '$')
			&& i > 0 && old[i - 1] == '\\')
		{
			fill[res - 1] = old[i];
			i++;
		}
		else if (old[i] == '$')
		{
			if (!(i > 0 && old[i - 1] == '\\'))
			{
				i++;
				size = size_var(old + i, envl, &current_var);
				if (current_var)
					ft_strlcpy(fill + res, current_var, size + 1);
				while (i < l && (ft_isalpha(old[i]) || old[i] == '_'))
					i++;
				res += size;
			}
		}
		fill[res] = old[i];
		res++;
		i++;
	}
	fill[res] = '\0';
}

void	expand_one(t_split *split, int i, t_list *envl)
{
	char	*old;
	int		size_tot;

	old = split[i].str;	
	size_tot = expanded_size(split[i].str, envl);
	split[i].str = malloc(size_tot * sizeof(char));
	if (!split[i].str)
		return ;
	fill_expanded(split[i].str, old, envl);
	free(old);
}

void	expand_db(t_info *cmd, t_split *split, t_list *envl)
{
	int	i;

	i = -1;
	while (++i < cmd->number)
	{
		if (split[cmd->start + i].sep == '\"' || split[cmd->start + i].sep == ' ')
			expand_one(split, cmd->start + i, envl);
	}
}
