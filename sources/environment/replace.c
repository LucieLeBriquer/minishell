/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:19:12 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/19 17:29:16 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			size_var(char *str, t_list *envl, char **value)
{
	char	*var;
	int		size;
	int		i;

	if (str[0] == '?')
		var = ft_strdup("?begin");
	else
	{
		size = ft_strlen(str);
		var = malloc((size + 1) * sizeof(char));
		if (!var)
			return (0);
		i = -1;
		while (++i < size && (ft_isalpha(str[i]) || str[i] == '_'))
			var[i] = str[i];
		var[i] = '\0';
	}
	*value = search_in_env(envl, var);
	free(var);
	if (!(*value))
		return (0);
	return (ft_strlen(*value));
}

static int	replace_var(int *i, char *old, t_list *envl, char *dest)
{
	int		size;
	int		l;
	char	*current_var;

	l = ft_strlen(old);
	size = size_var(old + ++(*i), envl, &current_var);
	if (current_var)
		ft_strlcpy(dest, current_var, size + 1);
	if (old[*i] == '?')
		(*i)++;
	else
	{
		while (*i < l && (ft_isalpha(old[*i]) || old[*i] == '_'))
			(*i)++;
	}
	return (size);
}

void		fill_expanded(char *fill, char *old, t_list *envl)
{
	int		l;
	int		res;
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
			if (i == 0 || old[i - 1] != '\\')
				res += replace_var(&i, old, envl, fill + res);
		}
		fill[res] = old[i];
		res++;
		i++;
	}
	fill[res] = '\0';
}
