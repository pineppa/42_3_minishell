/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:35:02 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 10:38:11 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*pdst;
	const char	*psrc;

	if (!dst && !src)
		return (NULL);
	pdst = (char *)dst;
	psrc = (char *)src;
	if (pdst < psrc)
	{
		while (len-- > 0)
			*pdst++ = *psrc++;
	}
	else
	{
		pdst += len - 1;
		psrc += len - 1;
		while (len-- > 0)
			*pdst-- = *psrc--;
	}
	return (dst);
}
