/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:49:52 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/13 18:36:36 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_var(char *var, char *value, t_list **envl, int exported)
{
	t_list	*new;
	t_env	*cont;

	new = malloc(sizeof(t_list));
	if (!new)
		return (ERROR);
	cont = malloc(sizeof(t_env));
	if (!cont)
	{
		free(new);
		return (ERROR);
	}
	cont->var = var;
	cont->value = value;
	cont->exported = 0;
	if (!value && exported == 2)
		cont->exported = 1;
	else if (value && exported == 2)
		cont->exported = 2;
	new->content = cont;
	new->next = NULL;
	ft_lstadd_back(envl, new);
	return (SUCCESS);
}

int			add_env(char *var, char *value, t_list **envl, int exported)
{
	t_list	*env;

	env = *envl;
	while (env)
	{
		if (ft_strcmp(((t_env *)env->content)->var, var) == 0)
		{
			if (value)
			{
				if (((t_env *)env->content)->value)
					free(((t_env *)env->content)->value);
				((t_env *)env->content)->value = value;
			}
			if (exported > ((t_env *)env->content)->exported)
				((t_env *)env->content)->exported = exported;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (add_new_var(var, value, envl, exported));
}

static int	export_one(char *var, t_list **envl, int exported)
{
	char	*varname;
	char	*value;
	char	*tmp;

	tmp = ft_strchr(var, '=');
	if (tmp)
	{
		value = ft_strdup(tmp + 1);
		tmp[0] = '\0';
		varname = ft_strdup(var);
	}
	else
	{
		value = NULL;
		varname = ft_strdup(var);
	}
	if (authorized_char(varname))
		return (add_env(varname, value, envl, exported));
	invalid_identifier(varname, "export", exported);
	free(varname);
	if (value)
		free(value);
	return (ERROR);
}

int			export_all(char **vars, t_list **envl, int exported)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (vars[i])
	{
		err += export_one(vars[i], envl, exported);
		i++;
	}
	if (err)
		return (ERROR);
	return (SUCCESS);
}