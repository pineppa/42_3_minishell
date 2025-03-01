/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:38:49 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/09 11:35:54 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	sz;

	sz = 0;
	while (*src)
	{
		sz++;
		if (size > 1)
		{
			size--;
			*dst++ = *src;
		}
		else if (size == 1)
		{
			size--;
			*dst = '\0';
		}
		src++;
	}
	if (size >= 1)
		*dst = '\0';
	return (sz);
}
