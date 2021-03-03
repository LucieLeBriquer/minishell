#include "minishell.h"

int	add_new_var(char *var, char *value, t_list **envl, int exported)
{
	t_list	*new;
	t_env	*cont;

	new = malloc(sizeof(t_list));
	if (!new)
		return (-1);
	cont = malloc(sizeof(t_env));
	if (!cont)
	{
		free(new);
		return (-1);
	}
	cont->var = var;
	cont->value = value;
	cont->exported = 1;
	if (value && exported == 2)
		cont->exported = 2;
	new->content = cont;
	new->next = NULL;
	ft_lstadd_back(envl, new);
	return (0);
}

int	add_env(char *var, char *value, t_list **envl, int exported)
{
	t_list	*env;

	env = *envl;
	while (env)
	{
		if (ft_strcmp(((t_env *)env->content)->var, var) == 0)
		{
			((t_env *)env->content)->value = value;
			((t_env *)env->content)->exported = exported;
			return (0);
		}
		env = env->next;
	}
	return (add_new_var(var, value, envl, exported));
	
}

int	export_one(char *var, t_list **envl)
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
		return (add_env(varname, value, envl, 2));
	return (-2);
}

int	export_all(char **vars, t_list **envl)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (vars[i])
	{
		err += export_one(vars[i], envl);
		i++;
	}
	if (err != 0)
		return (-1);
	return (0);
}
