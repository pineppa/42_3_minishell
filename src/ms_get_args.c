/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:36:33 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/19 11:18:32 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_add_args(t_cmd *c)
{
	int		i;
	t_arg	*a;

	i = 1;
	a = c->arl;
	while (a)
	{
		if (a->redir)
			a = a->nxa;
		else
			c->ara[i++] = a->ars;
		a = a->nxa;
	}
	return (0);
}

// convert the list of t_arg into null terminated array of strings
// as required by execve
// sanityze garantees that redir has next t_arg
// no need to free all c->ara, just the arl list and ara[0];
int	ms_get_args(t_cmd *c)
{
	t_arg	*a;
	int		i;

	i = 0;
	a = c->arl;
	while (a)
	{
		i += 1 - 2 * (a->redir != 0);
		a = a->nxa;
	}
	c->ara = ft_calloc(i + 2, sizeof(char *));
	if (!c->ara)
		return (EXIT_FAILURE);
	c->ara[0] = ft_strdup(c->cmd);
	if (!c->ara[0])
		return (EXIT_FAILURE);
	return (ms_add_args(c));
}
