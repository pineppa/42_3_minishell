/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_quo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:16:11 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/18 02:07:36 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ms_join_quo(t_arg *a)
{
	t_quo	*q;
	char	*ts;

	if (!a)
		return (NULL);
	a->ars = ft_free(a->ars);
	q = a->aq;
	while (q)
	{
		ts = a->ars;
		if (!a->ars)
			a->ars = ft_strdup(q->qs);
		else
			a->ars = ft_strjoin(a->ars, q->qs);
		ft_free(ts);
		if (!a->ars)
			return (NULL);
		q = q->nxq;
	}
	return (a);
}

t_quo	*ms_nxt_quo(t_arg *a, t_quo *tq, char c)
{
	tq->nxq = ms_new_quo(NULL);
	if (!tq->nxq)
		return (ms_free_quolst(a->aq));
	tq = tq->nxq;
	tq->q = ft_isquote(c) + (c == '"');
	return (tq);
}

// Check if there is an End Of quoted/unquoted element to split
// into a new t_quo
t_quo	*ms_check_eoq(t_arg *a, t_quo *tq, int *i, int *st)
{
	if (!tq->q && ft_isquote(a->ars[*i]))
	{
		tq->qs = ft_substr(a->ars, *st, *i - *st);
		tq = ms_nxt_quo(a, tq, a->ars[*i]);
		if (!tq)
			return (NULL);
		*st = (*i)++;
	}
	else if ((tq->q == 1 && a->ars[*i] == '\'')
		|| (tq->q == 2 && a->ars[*i] == '"'))
	{
		tq->qs = ft_substr(a->ars, *st, ++(*i) - *st);
		*st = *i;
		if (a->ars[*i])
		{
			tq->nxq = ms_new_quo(NULL);
			tq = ms_nxt_quo(a, tq, a->ars[*i]);
			if (!tq)
				return (NULL);
			(*i)++;
		}
	}
	else
		(*i)++;
	return (tq);
}

// Split arg into quoted and unquoted elements
// !a && !a->ars is checked before calling the function
// ars is trimmed
t_quo	*ms_split_quo(t_arg *a)
{
	t_quo	*tq;
	int		i;
	int		st;

	a->aq = ms_new_quo(NULL);
	if (!a->aq)
		return (NULL);
	tq = a->aq;
	tq->q = ft_isquote(a->ars[0]) + (a->ars[0] == '"');
	st = 0;
	i = (a->ars[0] != 0);
	while (a->ars[i])
	{
		tq = ms_check_eoq(a, tq, &i, &st);
		if (!tq)
			return (ms_free_quolst(a->aq));
	}
	if (i == 0)
		tq->qs = ft_strdup("");
	if (i > st)
		tq->qs = ft_substr(a->ars, st, i - st);
	tq = a->aq;
	return (a->aq);
}
