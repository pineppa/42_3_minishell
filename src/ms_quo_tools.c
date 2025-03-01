/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quo_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:30:13 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/05 19:39:37 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quo	*ms_new_quo(char *qs)
{
	t_quo	*rq;

	rq = ft_calloc(1, sizeof(t_quo));
	if (rq)
		rq->qs = qs;
	return (rq);
}

void	*ms_free_quo(t_quo *q)
{
	if (q)
		ft_free(q->qs);
	return (ft_free(q));
}

void	*ms_free_quolst(t_quo *q)
{
	if (!q)
		return (q);
	if (q->nxq)
		q->nxq = ms_free_quolst(q->nxq);
	return (ms_free_quo(q));
}
