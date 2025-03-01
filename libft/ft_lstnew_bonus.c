/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:43:19 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 18:00:25 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nl;

	nl = (t_list *) malloc(sizeof(t_list));
	if (nl)
	{
		nl->content = content;
		nl->next = NULL;
	}
	return (nl);
}
