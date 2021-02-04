/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:00:18 by lle-briq          #+#    #+#             */
/*   Updated: 2020/10/20 18:01:30 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*beg;

	beg = lst;
	while (beg && beg->next)
		beg = beg->next;
	return (beg);
}
