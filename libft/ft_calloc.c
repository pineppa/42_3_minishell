/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:28:08 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/15 13:38:37 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char		*rp;
	size_t		sz;

	sz = count * size;
	if (size && (sz / size) != count)
		return (NULL);
	rp = malloc(sz);
	if (rp != NULL)
		ft_bzero(rp, sz);
	return (rp);
}
