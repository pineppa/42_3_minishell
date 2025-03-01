/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:48:49 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/10 12:20:21 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	sz;

	sz = 0;
	while (*dst && (size > 0))
	{
		sz++;
		dst++;
		size--;
	}
	while (*src)
	{
		sz++;
		if (size > 1)
		{
			*dst++ = *src;
			size--;
		}
		src++;
	}
	if (size >= 1)
		*dst = '\0';
	return (sz);
}
