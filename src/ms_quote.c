/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:54:27 by jsala             #+#    #+#             */
/*   Updated: 2024/05/18 01:55:22 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ms_sig_quote(char c, int *sig_quote)
{
	if (!sig_quote)
		return (NULL);
	if (*sig_quote == 0)
	{
		if (c == '"')
			*sig_quote = 2;
		else if (c == '\'')
			*sig_quote = 1;
	}
	else if ((*sig_quote == 1 && c == 39) || (*sig_quote == 2 && c == 34))
		*sig_quote = 0;
	return (sig_quote);
}

// remove quotes from quoted elements in t_quo list
void	ms_quote_quo(t_quo *tq)
{
	int	i;

	if (!tq || !tq->q)
		return ;
	i = 0;
	while (i < (int)(ft_strlen(tq->qs) - 2))
	{
		tq->qs[i] = tq->qs[i + 1];
		i++;
	}
	tq->qs[i] = '\0';
}

// Remove quotes from quoted t_quo elements of all args of all commands
void	ms_quote(t_cmd *cmd)
{
	t_cmd	*tc;
	t_arg	*ta;
	t_quo	*tq;

	tc = cmd;
	while (tc)
	{
		ta = tc->arl;
		while (ta)
		{
			tq = ta->aq;
			while (tq)
			{
				ms_quote_quo(tq);
				tq = tq->nxq;
			}
			if (ta->aq)
				ms_join_quo(ta);
			ta = ta->nxa;
		}
		tc = tc->nxc;
	}
}
