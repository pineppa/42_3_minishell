/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:50:57 by josegar2          #+#    #+#             */
/*   Updated: 2024/02/22 16:39:48 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_ulog_base(unsigned long int n, int bn)
{
	int	len;

	len = (n == 0);
	while (n)
	{
		n = n / bn;
		len++;
	}
	return (len);
}

char	*ft_uitoa_base(unsigned long int n, char *base)
{
	int		l;
	int		b;
	char	*rstr;

	b = ft_strlen(base);
	l = ft_ulog_base(n, b);
	rstr = (char *) malloc(sizeof(char) * (l +1));
	if (!rstr)
		return (NULL);
	rstr[l--] = '\0';
	if (n == 0)
		rstr[0] = base[0];
	while (n)
	{
		rstr[l--] = base[n % b];
		n = n / b;
	}
	return (rstr);
}
