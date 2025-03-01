/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:16:48 by josegar2          #+#    #+#             */
/*   Updated: 2024/02/22 16:37:36 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnchar(char c, int n)
{
	int	sz;

	sz = 0;
	while (n-- > 0)
	{
		if (write(1, &c, 1) == 1)
			sz++;
		else
			return (-1);
	}
	return (sz);
}

int	ft_prfchar_c(char c, t_flags fl)
{
	int		sz;

	sz = 0;
	if (!fl.minus && fl.zero)
		sz += ft_putnchar('0', fl.width - 1);
	else if (!fl.minus)
		sz += ft_putnchar(' ', fl.width - 1);
	if (sz >= 0)
		sz += ft_putnchar(c, 1);
	if (fl.minus && sz >= 0)
		sz += ft_putnchar(' ', fl.width - 1);
	return (sz);
}

int	ft_prfchar(va_list args, t_flags fl)
{
	char	c;
	int		sz;

	sz = 0;
	c = (char) va_arg(args, int);
	if (!fl.minus && fl.zero)
		sz += ft_putnchar('0', fl.width - 1);
	else if (!fl.minus)
		sz += ft_putnchar(' ', fl.width - 1);
	if (sz >= 0)
		sz += ft_putnchar(c, 1);
	if (fl.minus && sz >= 0)
		sz += ft_putnchar(' ', fl.width - 1);
	return (sz);
}
