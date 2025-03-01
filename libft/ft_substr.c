/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:22:22 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 12:03:07 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lstr;
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	lstr = ft_strlen(s);
	if (start > lstr)
		len = 0;
	else
		if (len > (lstr - start))
			len = lstr - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (str);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
