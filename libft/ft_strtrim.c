/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:16:25 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 12:02:43 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rstr;
	int		st;
	int		end;

	if (!s1 || !set)
		return (NULL);
	st = 0;
	end = ft_strlen(s1) -1;
	while (ft_isinset(s1[st], set) && st <= end)
		st++;
	if (st > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_isinset(s1[end], set) && end >= 0)
		end--;
	rstr = malloc(sizeof(char) * (end - st + 2));
	if (!rstr)
		return (rstr);
	ft_strlcpy(rstr, s1 + st, end - st + 2);
	return (rstr);
}
