#include "minishell.h"

int		size_var(char *str, t_list *envl)
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
	//searc
}

int		expanded_size(char *str, t_list *envl)
{
	int	i;
	int	res;
	int	l;

	l = ft_strlen(str);
	while (i < l)
	{
		if (str[i] == '\\')
			i++;
		if (str[i] == '$')
		{
			i++;
			res += size_var(str + i, envl);
			while (i < l && (ft_isalpha(str[i]) || str[i] == '_')
				i++;
		}
		i++;
	}
}

void	expand_one(t_split *split, int i, t_list *envl)
{
	char	*old;
	int		size_tot;

	old = split[i].str;	
	size_tot = expanded_size(split[i].str, envl);
	split[i].str = malloc(size_tot * sizeof(char));
}

void	expand_db(t_info *cmd, t_split *split, t_list *envl)
{
	int	i;

	i = -1;
	while (++i < cmd->number)
	{
		if (split[cmd->start + i].quote = '\"')
			expand_db(split, cmd->start + i, envl);
	}
}
