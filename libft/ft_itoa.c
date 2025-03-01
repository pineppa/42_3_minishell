/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:50:57 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 12:29:00 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_log(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*rstr;

	l = ft_log(n);
	rstr = (char *) malloc(sizeof(char) * (l +1));
	if (!rstr)
		return (NULL);
	rstr[l--] = '\0';
	if (n < 0)
		rstr[0] = '-';
	if (n == 0)
		rstr[0] = '0';
	while (n)
	{
		if (n < 0)
			rstr[l--] = '0' + -1 * (n % 10);
		else
			rstr[l--] = '0' + (n % 10);
		n = n / 10;
	}
	return (rstr);
}
