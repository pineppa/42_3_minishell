/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:37:49 by josegar2          #+#    #+#             */
/*   Updated: 2024/02/22 16:37:18 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_flag(const char *c)
{
	int	test;

	test = (*c == '-') || (*c == '0') || (*c == '\'');
	test = test || (*c == '#') || (*c == ' ') || (*c == '+');
	return (test);
}

void	ft_flags_init(t_flags *tf)
{
	tf -> minus = 0;
	tf -> zero = 0;
	tf -> point = 0;
	tf -> hash = 0;
	tf -> space = 0;
	tf -> plus = 0;
	tf -> width = 0;
	tf -> precision = -1;
}

void	ft_flags_set(const char	*c, t_flags *tf)
{
	tf -> minus += *c == '-';
	tf -> zero += *c == '0';
	tf -> point += *c == '\'';
	tf -> hash += *c == '#';
	tf -> space += *c == ' ';
	tf -> plus += *c == '+';
	if (tf -> zero && tf -> minus)
		tf -> zero = 0;
	if (tf -> space && tf -> plus)
		tf -> space = 0;
}
