/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:32:14 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/15 13:37:42 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rlst;
	t_list	*ilst;

	if (!lst)
		return (lst);
	rlst = NULL;
	while (lst)
	{
		ilst = (t_list *) malloc(sizeof(t_list));
		if (!ilst)
		{
			if (rlst)
				ft_lstclear(&rlst, del);
			return (NULL);
		}
		ilst -> content = f(lst -> content);
		ilst -> next = NULL;
		if (!rlst)
			rlst = ilst;
		else
			ft_lstadd_back(&rlst, ilst);
		lst = lst -> next;
	}
	return (rlst);
}
