#include "minishell.h"

int		expand_then_add(t_list **words, char *str, char sep, int space, t_list *envl, t_list **seps, t_list **spaces)
{
	if (sep == '\"')
	{
		expand_simple(words, str, envl);
		ft_lstadd_back(seps, ft_lstnew("\""));
	}
	else
		expand_hard(words, str, envl, seps, spaces);
	if (space)
		ft_lstadd_back(spaces, ft_lstnew("1"));
	else
		ft_lstadd_back(spaces, ft_lstnew("0"));
	return (SUCCESS);
}

static int	list_to_tab(t_list *words, t_list *seps, t_list *spaces, t_info *cmd)
{
	int	i;

	cmd->nb_args_tmp = list_size(words);
	cmd->args_tmp = malloc((cmd->nb_args + 1) * sizeof(char *));
	cmd->seps_tmp = malloc((cmd->nb_args + 1) * sizeof(char));
	cmd->spaces_tmp = malloc((cmd->nb_args + 1) * sizeof(int));
	if (!cmd->args_tmp || !cmd->seps_tmp || !cmd->spaces_tmp)
		return (ALLOCATION_FAIL);
	i = -1;
	while (++i < cmd->nb_args_tmp)
	{
		cmd->args_tmp[i] = ft_strdup((char *)words->content);
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

int		new_expand(t_info *cmd, t_list *envl, t_split *split)
{
	int		i;
	t_list	*words;
	t_list	*seps;
	t_list	*spaces;
	t_list	*new;
	char	*str;
	char	sep;
	int		space;

	i = -1;
	words = NULL;
	seps = NULL;
	spaces = NULL;
	while (++i < cmd->number)
	{
		space = split[cmd->start + i].space;
		str = split[cmd->start + i].str;
		sep = split[cmd->start + i].sep;
		if (sep == '\"' || sep == ' ')
			expand_then_add(&words, str, sep, space, envl, &seps, &spaces);
		else
		{
			new = ft_lstnew(ft_strdup(str));
			ft_lstadd_back(&words, new);
			ft_lstadd_back(&seps, ft_lstnew(char_to_string(sep)));
			ft_lstadd_back(&spaces, ft_lstnew(ft_itoa(space)));
		}
	}
	if (list_to_tab(words, seps, spaces, cmd))
		return (ALLOCATION_FAIL);
	join_args(cmd);
	return (SUCCESS);
}
