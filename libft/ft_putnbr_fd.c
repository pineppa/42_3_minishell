/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:16:42 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 16:41:05 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	istr[12];
	int		i;
	int		neg;

	neg = 1 * (n >= 0) - 1 * (n < 0);
	i = 11;
	istr[i--] = '\0';
	while (((n / 10) * neg) > 0)
	{
		istr[i--] = '0' + (n % 10) * neg;
		n = n / 10;
	}
	istr[i] = '0' + (n % 10) * neg;
	if (neg == -1)
		istr[--i] = '-';
	ft_putstr_fd(&istr[i], fd);
}
