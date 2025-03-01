/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:35:24 by josegar2          #+#    #+#             */
/*   Updated: 2024/04/03 18:00:16 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_atoi(const char *str)
{
	int	signo;
	int	valor;

	signo = 1;
	while (ft_isspace(*str))
	{
		str++;
	}
	if (*str == '-')
	{
		signo = -signo;
		str++;
	}
	else if (*str == '+')
		str++;
	valor = 0;
	while (*str >= '0' && *str <= '9')
	{
		valor = valor * 10 + (*str - '0');
		str++;
	}
	return (signo * valor);
}
