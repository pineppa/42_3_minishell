/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:46:05 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/12 17:56:00 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;

	if (lst)
	{
		l = *lst;
		if (l)
		{
			if (l -> next)
				ft_lstclear(&(l -> next), del);
			ft_lstdelone(l, del);
		}
		*lst = NULL;
	}
}
