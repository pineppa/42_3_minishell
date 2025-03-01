/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:59:36 by josegar2          #+#    #+#             */
/*   Updated: 2024/02/22 16:53:14 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_split_1nl(char	**s)
{
	char	*nl;
	char	*ts;

	nl = ft_strchr(*s, '\n');
	if (nl)
	{
		nl = ft_substr(*s, 0, nl - *s + 1);
		if (!nl)
			return (NULL);
		ts = *s;
		*s = ft_substr(*s, ft_strlen(nl), ft_strlen(*s) - ft_strlen(nl));
		free(ts);
		if (!*s)
		{
			free(nl);
			return (NULL);
		}
	}
	return (nl);
}
