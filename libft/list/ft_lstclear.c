/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:08:22 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/17 16:24:18 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*beg;
	t_list	*save;

	if (!lst)
		return ;
	beg = *lst;
	while (beg)
	{
		save = beg->next;
		ft_lstdelone(beg, del);
		beg = save;
	}
	*lst = NULL;
}
