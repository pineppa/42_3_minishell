/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:43:29 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/18 01:42:19 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		sz;
	char	*str;
	char	*tstr;

	if (!s1 | !s2)
		return (NULL);
	sz = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (sz + 1));
	if (str != NULL)
	{
		tstr = str;
		while (*s1)
			*tstr++ = *s1++;
		while (*s2)
			*tstr++ = *s2++;
		*tstr = '\0';
	}
	return (str);
}
