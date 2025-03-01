/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:57:23 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/06 19:11:19 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_error(char *msg1, char *msg2, char *msg3, int head)
{
	if (head)
		write(2, "minishell: ", 11);
	while (msg1 && *msg1 != '\0')
		write(2, msg1++, 1);
	while (msg2 && *msg2 != '\0')
		write(2, msg2++, 1);
	while (msg3 && *msg3 != '\0')
		write(2, msg3++, 1);
	write(2, "\n", 1);
	return (0);
}

int	ms_error_putc(char c)
{
	if (write(2, &c, 1) < 0)
	{
		printf("Error writing on stdout");
		exit(1);
	}
	return (1);
}

int	ms_error_puts(char *s)
{
	if (write(2, s, ft_strlen(s)) < 0)
	{
		printf("Error writing on stdout");
		exit(1);
	}
	return (1);
}

int	ms_error_head(char *head)
{
	if (head)
	{
		ms_error_puts(head);
		ms_error_puts(": ");
	}
	return (0);
}

// missing initial minishell: and check of writes
int	ms_errorf(char *head, char *f, char *s0, char *s1)
{
	char	*s[3];
	int		i;

	s[0] = s0;
	s[1] = s1;
	i = ms_error_head(head);
	while (*f)
	{
		if (*f == '%' && *(f + 1) == 'c' && i < 2 && s[i])
		{
			i += ms_error_putc(*s[i]);
			f += 2;
		}
		else if (*f == '%' && *(f + 1) == 's' && i < 2 && s[i])
		{
			i += ms_error_puts(s[i]);
			f += 2;
		}
		else
			write(2, f++, 1);
	}
	ms_error_puts("\n");
	return (0);
}
