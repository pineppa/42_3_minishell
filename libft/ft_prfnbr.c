/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prfdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:52:14 by josegar2          #+#    #+#             */
/*   Updated: 2024/02/22 16:38:15 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pre_lead(t_flags fl, int isuint, int isneg, int *len)
{
	int	sz;

	sz = 0;
	if (!isuint && !isneg)
	{
		if (fl.space && !fl.plus)
			sz = write(1, " ", 1);
		else if (fl.plus && (fl.zero || fl.minus || (*len + 1) >= fl.width))
			sz = write(1, "+", 1);
		if (sz == 1 || (fl.plus && !isneg))
			(*len)++;
	}
	if (isneg && (fl.zero || fl.minus || *len >= fl.width))
		sz = write(1, "-", 1);
	return (sz);
}

static int	ft_pre_nbr(t_flags fl, int isuint, int isneg, int len)
{
	int	sz;
	int	wr;

	if (fl.precision >= 0 && (fl.precision > len - isneg))
		len = fl.precision + isneg;
	sz = ft_pre_lead(fl, isuint, isneg, &len);
	wr = 0;
	if (sz >= 0 && !fl.minus && !fl.zero)
		wr = ft_putnchar(' ', fl.width - len);
	else if (sz >= 0 && !fl.minus && fl.width > len)
		wr = ft_putnchar('0', fl.width - len);
	if (sz < 0 || wr < 0)
		return (-1);
	sz += wr;
	wr = 0;
	if (isneg && !fl.zero && !fl.minus && len < fl.width)
		wr = write(1, "-", 1);
	if (!isneg && !isuint && fl.plus && !fl.zero && !fl.minus)
		wr = write(1, "+", len < fl.width);
	if (wr < 0)
		return (-1);
	return (sz + wr);
}

int	ft_absnbr(char *str, int len, int sz, t_flags fl)
{
	int	wr;

	if (sz >= 0)
	{
		wr = 0;
		if (fl.precision > len - (*str == '-'))
			wr = ft_putnchar('0', fl.precision - len + (*str == '-'));
		if (wr < 0)
			return (-1);
		sz += wr;
		if (*str == '-')
			len = write(1, &str[1], len - 1);
		else
			len = write(1, str, len);
	}
	if (sz < 0 || len < 0)
		return (-1);
	return (sz + len);
}

int	ft_prfnbr(va_list args, t_flags fl, int isuint)
{
	int		sz;
	int		len;
	int		value;
	char	*str;

	value = va_arg(args, int);
	if (isuint)
		str = ft_uitoa((unsigned int) value);
	else
		str = ft_itoa(value);
	if (!str)
		return (-1);
	len = ft_strlen(str) * (value != 0 || fl.precision != 0);
	fl.zero = fl.zero && fl.precision < 0;
	sz = ft_pre_nbr(fl, isuint, *str == '-', len);
	if (value != 0 || fl.precision != 0)
		sz = ft_absnbr(str, len, sz, fl);
	free(str);
	len = 0;
	if (sz >= 0 && fl.minus)
		len = ft_putnchar(' ', fl.width - sz);
	if (len < 0)
		return (-1);
	return (sz + len);
}
