/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:38:45 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/16 14:08:13 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO:
// bash-3.2$ AA="   "
// bash-3.2$ ls < $AA"a"$AA
// bash: a: No such file or directory
// bash-3.2$ ls < $AA""$AA
// bash: $AA""$AA: ambiguous redirect
// bash-3.2$ ls < ""
// bash: : No such file or directory
int	ms_redir_checksplit(t_arg *ar, t_quo *q)
{
	int		i;
	int		st;
	char	*rs;

	i = 0;
	rs = q->qs;
	if (q == ar->aq)
		while (ft_isspace(rs[i]))
			i++;
	st = i;
	while (rs[i])
	{
		if (ft_isspace(rs[i]))
		{
			return (1);
		}
		i++;
	}
	q->qs = ft_substr(rs, st, i - st);
	ft_free (rs);
	return (0);
}

// Expand operand of redirection
// If there is a space in the middle after expansion 
// of unquoted t_quo it returns NULL
// TDOD: check ar is not redir and not NULL or sanitize is enough?
t_arg	*ms_redir_exp(t_shell *sh, t_arg *ar)
{
	char	*ts;
	t_quo	*tq;

	if (!ar || !ar->ars)
		return (NULL);
	tq = ms_split_quo(ar);
	while (tq)
	{
		if (tq->q == 0 || tq->q == 2)
		{
			ts = tq->qs;
			tq->qs = ms_strexp(sh, tq->qs);
			ft_free(ts);
			if (tq->q == 0)
			{
				if (ms_redir_checksplit(ar, tq))
				{
					ms_errorf("minishell", AMBREDIR, ar->ars, NULL);
					return (NULL);
				}
			}
		}
		tq = tq->nxq;
	}
	return (ms_join_quo(ar));
}

t_arg	*ms_redir_quo(t_arg *ar)
{
	t_quo	*tq;

	tq = ar->aq;
	while (tq)
	{
		ms_quote_quo(tq);
		tq = tq->nxq;
	}
	if (ar->aq)
		ms_join_quo(ar);
	return (ar);
}
