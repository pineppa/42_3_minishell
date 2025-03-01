/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:06:34 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/18 01:43:16 by jlgarcia         ###   ########.fr       */
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

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*idest;

	idest = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (idest);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;

	if (!s1)
		return (NULL);
	dest = (char *)malloc(sizeof(char) *(ft_strlen(s1) + 1));
	if (dest)
		dest = ft_strcpy(dest, s1);
	return (dest);
}
