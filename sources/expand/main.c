/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:07:28 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/17 18:07:31 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		expand_then_add(t_list **expansion, t_split curr, t_list *envl, int r)
{
	if (curr.sep == '\"')
	{
		expand_simple(expansion, curr, envl);
		return (SUCCESS);
	}
	return (expand_hard(expansion, curr, envl, r));
}

static int	list_to_tab(t_list *expansion, t_info *cmd)
{
	t_split	*curr;
	int		i;

	cmd->nb_args_tmp = list_size(expansion);
	cmd->args_tmp = malloc((cmd->nb_args_tmp + 1) * sizeof(char *));
	cmd->seps_tmp = malloc((cmd->nb_args_tmp + 1) * sizeof(char));
	cmd->spaces_tmp = malloc((cmd->nb_args_tmp + 1) * sizeof(int));
	if (!cmd->args_tmp || !cmd->seps_tmp || !cmd->spaces_tmp)
		return (ALLOCATION_FAIL);
	i = -1;
	while (++i < cmd->nb_args_tmp)
	{
		curr = expansion->content;
		cmd->args_tmp[i] = ft_strdup(curr->str);
		cmd->seps_tmp[i] = curr->sep;
		cmd->spaces_tmp[i] = curr->space;
		expansion = expansion->next; 
	}
	cmd->args_tmp[i] = NULL;
	cmd->seps_tmp[i] = '\0';
	cmd->spaces_tmp[i] = -1;
	return (SUCCESS);
}

int		expand_one(t_list **expansion, t_list *envl, t_split curr, int *redir)
{
	int	err;

	err = SUCCESS;
	if (curr.sep == '\"' || curr.sep == ' ')
		err = expand_then_add(expansion, curr, envl, *redir);
	else
		ft_lstadd_back(expansion, new_entry(curr.str, curr.sep, curr.space));
	if (err)
		return (AMBIGUOUS_REDIR);
	*redir = 0;
	if (is_redir(curr.sep))
		*redir = 1;
	return (SUCCESS);
}

int		expand(t_info *cmd, t_list *envl, t_split *split)
{
	t_list	*expansion;
	int		i;
	int		redir;
	int		err;

	i = -1;
	expansion = NULL;
	err = SUCCESS;
	redir = 0;
	while (++i < cmd->number && !err)
		err = expand_one(&expansion, envl, split[cmd->start + i], &redir);
	if (err || list_to_tab(expansion, cmd))
	{
		ft_lstclear(&expansion, &free_expd);
		if (err)
			return (AMBIGUOUS_REDIR);
		return (ALLOCATION_FAIL);
	}
	ft_lstclear(&expansion, &free_expd);
	return (join_args(cmd));
}
