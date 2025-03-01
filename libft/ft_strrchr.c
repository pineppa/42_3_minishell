/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:38:49 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/09 12:20:34 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*rstr;

	rstr = NULL;
	while (*s)
	{
		if (*s == (char) c)
			rstr = s;
		s++;
	}
	if (*s == (char) c)
		rstr = s;
	return ((char *) rstr);
}
