/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_ms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:35:24 by josegar2          #+#    #+#             */
/*   Updated: 2024/03/28 16:29:15 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return 0 if long is correct
//		  1 if not numeric or out of max/min LONG
//				error expected in exit argument
// value is returned in lv
int	ft_atol_ms(char *s, long *lv)
{
	int				sign;
	unsigned long	value;

	if (*s != '-' && *s != '+' && !ft_isdigit(*s))
		return (1);
	sign = (*s != '-') - (*s == '-');
	s += (*s == '+' || *s == '-');
	while (*s == '0' && *(s + 1) == '0')
		s++;
	if (!*s || ft_strlen(s) > 19)
		return (1);
	value = 0;
	while (*s)
	{
		if (ft_isdigit(*s))
			value = value * 10 + (*s - '0');
		else
			return (1);
		s++;
	}
	if ((sign == 1 && value > LONG_MAX)
		|| (sign == -1 && (value - 1) > LONG_MAX))
		return (1);
	*lv = (long) sign * value;
	return (0);
}
