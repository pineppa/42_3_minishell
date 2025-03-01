/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prfhexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:53:21 by josegar2          #+#    #+#             */
/*   Updated: 2024/02/22 16:37:55 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhash(t_flags tf, int isupper, int iszero)
{
	if (tf.hash && isupper && !iszero)
		return (write(1, "0X", 2));
	else if (tf.hash && !iszero)
		return (write(1, "0x", 2));
	return (0);
}

static int	ft_pre_hex(t_flags tf, int isupper, int len, int iszero)
{
	int	sz;
	int	wr;

	sz = 0;
	tf.hash = tf.hash && !iszero;
	if (tf.precision >= 0 && (tf.precision > len))
		len = tf.precision;
	if (!tf.minus && !tf.zero)
		sz = ft_putnchar(' ', tf.width - len - 2 * tf.hash);
	if (sz < 0)
		return (-1);
	wr = ft_printhash(tf, isupper, iszero);
	if (wr < 0)
		return (-1);
	sz += wr;
	wr = 0;
	if (!tf.minus && tf.zero)
		wr = ft_putnchar('0', tf.width - sz - len);
	if (wr < 0)
		return (-1);
	return (sz + wr);
}

int	ft_pr_adjhexa(int sz, t_flags tf, char *str, int len)
{
	int	wr;

	if (sz >= 0)
	{
		wr = 0;
		if (tf.precision > len)
			wr = ft_putnchar('0', tf.precision - len);
		if (wr < 0)
			return (-1);
		sz += wr;
		wr = write(1, str, len);
	}
	if (sz < 0 || wr < 0)
		return (-1);
	return (sz + wr);
}

int	ft_prfhexa(va_list args, t_flags tf, int isupper, int isptr)
{
	int					sz;
	int					len;
	unsigned long int	value;
	char				*base[2];
	char				*str;

	base[0] = "0123456789abcdef";
	base[1] = "0123456789ABCDEF";
	if (isptr)
		value = (unsigned long int)va_arg(args, void *);
	else
		value = (unsigned long int) va_arg(args, unsigned int);
	str = ft_uitoa_base(value, base[isupper]);
	if (!str)
		return (-1);
	len = ft_strlen(str) * (value != 0 || tf.precision != 0);
	tf.zero = tf.zero && tf.precision < 0;
	sz = ft_pre_hex(tf, isupper, len, value == 0 && !isptr);
	sz = ft_pr_adjhexa(sz, tf, str, len);
	free(str);
	if ((sz >= 0) && tf.minus)
		sz += ft_putnchar(' ', tf.width - sz);
	return (sz);
}
