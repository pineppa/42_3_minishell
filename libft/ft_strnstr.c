/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:48:49 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/10 16:03:00 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	const char	*ps1;
	const char	*ps2;
	int			eq;
	size_t		tn;

	if (*s2 == '\0')
		return ((char *)s1);
	while (*s1 && n-- > 0)
	{
		if (*s1 == *s2)
		{
			ps1 = s1;
			ps2 = s2;
			eq = 1;
			tn = n + 1;
			while (eq && *ps2)
				eq = eq & (*ps1++ == *ps2++) & (tn-- > 0);
			if (eq)
				return ((char *)s1);
		}
		s1++;
	}
	return (NULL);
}
