/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:14:57 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 18:19:28 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	l;

	l = 0;
	if (lst)
	{
		l = 1;
		while (lst -> next)
		{
			lst = lst -> next;
			l++;
		}
	}
	return (l);
}
