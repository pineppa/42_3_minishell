/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:38:49 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/09 11:23:21 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*rstr;

	rstr = (char *)s;
	while (n-- > 0)
	{
		if (*rstr == (char) c)
			return (rstr);
		rstr++;
	}
	return (NULL);
}
