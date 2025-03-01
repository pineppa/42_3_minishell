/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:48:49 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 10:39:14 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*ss1;
	const char	*ss2;

	if (!s1 && !s2)
		return (0);
	ss1 = (const char *) s1;
	ss2 = (const char *) s2;
	while (n > 0)
	{
		if (*ss1 != *ss2)
			return ((unsigned char) *ss1 - (unsigned char) *ss2);
		ss1++;
		ss2++;
		n--;
	}
	return (0);
}
