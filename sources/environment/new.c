#include "minishell.h"

int		expand_then_add(t_list **words, char *str, char sep, int space, t_list *envl, t_list **seps, t_list **spaces, int r)
{
	int	err;

	err = SUCCESS;
	if (sep == '\"')
	{
		expand_simple(words, str, envl);
		ft_lstadd_back(seps, ft_lstnew(char_to_string(sep)));
	}
	else
		err = expand_hard(words, str, envl, seps, spaces, r);
	ft_lstadd_back(spaces, ft_lstnew(ft_itoa(space)));
	return (err);
}

static int	list_to_tab(t_list *words, t_list *seps, t_list *spaces, t_info *cmd)
{
	int	i;

	cmd->nb_args_tmp = list_size(words);
	cmd->args_tmp = malloc((cmd->nb_args_tmp + 1) * sizeof(char *));
	cmd->seps_tmp = malloc((cmd->nb_args_tmp + 1) * sizeof(char));
	cmd->spaces_tmp = malloc((cmd->nb_args_tmp + 1) * sizeof(int));
	if (!cmd->args_tmp || !cmd->seps_tmp || !cmd->spaces_tmp)
		return (ALLOCATION_FAIL);
	i = -1;
	while (++i < cmd->nb_args_tmp)
	{
		cmd->args_tmp[i] = ft_strdup((char *)(words->content));
		cmd->seps_tmp[i] = ((char *)seps->content)[0];
		cmd->spaces_tmp[i] = ((char *)spaces->content)[0] - '0';
		words = words->next; 
		seps = seps->next;
		spaces = spaces->next;
	}
	cmd->args_tmp[i] = NULL;
	cmd->seps_tmp[i] = '\0';
	cmd->spaces_tmp[i] = -1;
	return (SUCCESS);
}

char	*char_to_string(char c)
{
	char *str;

	str = malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int		is_redir(char c)
{
	if (c == '>' || c == 'd' || c == '<')
		return (1);
	return (0);
}

int		new_expand(t_info *cmd, t_list *envl, t_split *split)
{
	int		i;
	t_list	*words;
	t_list	*seps;
	t_list	*spaces;
	t_list	*new;
	char	*str;
	char	sep;
	int		r;
	int		space;
	int		err;

	i = -1;
	words = NULL;
	seps = NULL;
	spaces = NULL;
	r = 0;
	err = 0;
	while (++i < cmd->number)
	{
		space = split[cmd->start + i].space;
		str = split[cmd->start + i].str;
		sep = split[cmd->start + i].sep;
		if (sep == '\"' || sep == ' ')
			err = expand_then_add(&words, str, sep, space, envl, &seps, &spaces, r);
		else
		{
			new = ft_lstnew(ft_strdup(str));
			ft_lstadd_back(&words, new);
			ft_lstadd_back(&seps, ft_lstnew(char_to_string(sep)));
			ft_lstadd_back(&spaces, ft_lstnew(ft_itoa(space)));
		}
		if (err)
			break ;
		r = 0;
		if (is_redir(sep))
			r = 1;
	}
	if (err || list_to_tab(words, seps, spaces, cmd))
	{
		free_lists(&words, &seps, &spaces);
		if (err)
		{
			ft_printf("ambiguous\n");
			return (AMBIGUOUS_REDIR);
		}
		return (ALLOCATION_FAIL);
	}
	free_lists(&words, &seps, &spaces);
	return (join_args(cmd));
}
