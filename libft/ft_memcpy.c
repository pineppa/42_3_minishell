/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:48:49 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 10:34:53 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char	*rs1;

	if (!s1 && !s2)
		return (s1);
	rs1 = (char *) s1;
	while (n-- > 0)
	{
		*rs1++ = *(char *)s2++;
	}
	return (s1);
}
/*
#include <string.h>

int	main()
{
	memcpy(((void *)0), ((void *)0), 3);
	//ft_memcpy(((void *)0), ((void *)0), 3);
}
*/
