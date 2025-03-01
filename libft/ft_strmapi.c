/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:20:34 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 15:43:55 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*rstr;

	if (!s)
		return (NULL);
	rstr = ft_strdup(s);
	if (!rstr)
		return (rstr);
	i = 0;
	while (s[i])
	{
		rstr[i] = (*f)(i, s[i]);
		i++;
	}
	return (rstr);
}
