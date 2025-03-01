/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prfstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:51:34 by josegar2          #+#    #+#             */
/*   Updated: 2024/02/22 16:38:44 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_prfstr(va_list args, t_flags fl)
{
	int		sz;
	int		len;
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (fl.precision >= 0 && fl.precision < len)
		len = fl.precision;
	sz = 0;
	if (!fl.minus && fl.zero && fl.width > len)
		sz = ft_putnchar('0', fl.width - len);
	else if (!fl.minus && fl.width > len)
		sz = ft_putnchar(' ', fl.width - len);
	if (sz < 0 || write(1, str, len) < 0)
		return (-1);
	sz = sz + len;
	if (fl.minus && fl.width > len)
		len = ft_putnchar(' ', fl.width - len);
	else
		len = 0;
	if (len < 0)
		return (-1);
	return (sz + len);
}
