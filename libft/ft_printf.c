/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:19:19 by josegar2          #+#    #+#             */
/*   Updated: 2024/02/22 16:39:10 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_prec_set(const char **pc, t_flags *tf)
{
	if (ft_isdigit((int) **pc))
	{
		tf -> width = ft_atoi(*pc);
		while (ft_isdigit((int) **pc))
			(*pc)++;
	}
	if (**pc == '.')
	{
		(*pc)++;
		tf -> precision = ft_atoi(*pc);
		while (ft_isdigit((int) **pc))
			(*pc)++;
	}
}

int	ft_print_arg(const char *c, t_flags fl, va_list args)
{
	int	sz;

	sz = 0;
	if (*c == '%')
		return (ft_prfchar_c('%', fl));
	if (*c == 'c')
		return (ft_prfchar(args, fl));
	if (*c == 's')
		return (ft_prfstr(args, fl));
	if (*c == 'p')
	{
		fl.hash = 1;
		return (ft_prfhexa(args, fl, 0, 1));
	}
	if (*c == 'd' || *c == 'i' || *c == 'u')
		return (ft_prfnbr(args, fl, (*c == 'u')));
	if (*c == 'x' || *c == 'X')
		return (ft_prfhexa(args, fl, (*c == 'X'), 0));
	return (sz);
}

int	ft_parse(const char *c, va_list args)
{
	int			sz;
	int			wr;
	t_flags		flags;

	sz = 0;
	while (*c)
	{
		if (*c != '%')
			wr = write(1, c++, 1);
		else
		{
			c++;
			ft_flags_init(&flags);
			while (*c && is_flag(c))
				ft_flags_set(c++, &flags);
			if (*c && (ft_isdigit((int) *c) || *c == '.'))
				ft_prec_set(&c, &flags);
			if (*c && (ft_strchr("cspdiuxX%", (int) *c)))
				wr = ft_print_arg(c++, flags, args);
		}
		if (wr < 0)
			return (-1);
		sz += wr;
	}
	return (sz);
}

int	ft_printf(const char *format, ...)
{
	int			sz;
	va_list		args;

	if (!format)
		return (0);
	va_start(args, format);
	sz = ft_parse(format, args);
	va_end(args);
	return (sz);
}
