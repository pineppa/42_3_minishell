/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strexp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:28:34 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/18 02:06:44 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Funtion that creates a new string by adding a char
// to the original string and freeing it
char	*ms_straddchar(char *s, char c)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	ft_free(s);
	return (str);
}

char	*ms_strexp(t_shell *sh, char *s)
{
	int		q;
	char	*rs;
	char	*ts;
	char	*vs;

	if (!s)
		return (s);
	q = 0;
	rs = ft_strdup("");
	while (rs && *s)
	{
		ts = rs;
		if (*s == '$' && q != 1)
		{
			vs = ms_exp_var(sh, &s);
			rs = ft_strjoin(rs, vs);
			ft_free(vs);
			ft_free(ts);
			continue ;
		}
		else if ((*s == '"' && q != 1) || (*s == '\'' && q != 2))
			q = (1 + (*s == '"')) * (q == 0);
		rs = ms_straddchar(rs, *s++);
	}
	return (rs);
}

// Function called when in a expanded unquoted t_quo (q==0)
// an space is found
// It must create a new quo in a new arg with the rest of the string
// and the next quo
t_arg	*ms_ws_newarg(t_arg *ar, t_quo *tq, char *rs, int i)
{
	t_arg	*ra;
	t_quo	*nq;

	nq = ms_new_quo(NULL);
	if (!nq)
		return (ms_error("new_quo: ", strerror(errno), NULL, 1), NULL);
	nq->nxq = tq->nxq;
	nq->qs = ft_substr(rs, i, ft_strlen(rs) - i);
	if (!nq->qs)
	{
		ms_free_quo(nq);
		return (ms_error("new_quo : ", strerror(errno), NULL, 1), NULL);
	}
	ra = ft_argnew(NULL);
	if (!ra)
	{
		ms_free_quo(nq);
		return (ms_error("new_quo  : ", strerror(errno), NULL, 1), NULL);
	}
	ra->nxa = ar->nxa;
	ra->aq = nq;
	ar->nxa = ra;
	tq->nxq = NULL;
	return (ar);
}

// This function will be called after expanding vars and
// just for the t_quo with q == 0
// ar: initial t_arg expanding
// q: * to actual expanded t_quo element
// If there is some space it will end the t_quo list and
// create a new arg with the rest of the t_quo list
t_arg	*ms_wordsplit_q(t_arg *ar, t_quo **q)
{
	int		i;
	int		st;
	char	*rs;

	i = 0;
	rs = (*q)->qs;
	if (*q == ar->aq)
		while (ft_isspace(rs[i]))
			i++;
	st = i;
	while (rs[i])
	{
		if (ft_isspace(rs[i]))
		{
			if (!ms_ws_newarg(ar, *q, rs, i))
				return (NULL);
			break ;
		}
		while (rs[i] && !ft_isspace(rs[i]))
			i++;
	}
	(*q)->qs = ft_substr(rs, st, i - st);
	ft_free (rs);
	return (ar);
}

// Do var expansion of arg and word split
// To do it, first split into quotes and unquoted parts of the arg
// or takes the previous split if there was a word splitting
// word split just apply to unquoted parts of the string
t_arg	*ms_argexp(t_shell *sh, t_arg *ar)
{
	char	*ts;
	t_quo	*tq;

	if (ar->ars)
		tq = ms_split_quo(ar);
	else
		tq = ar->aq;
	if (!tq)
		return (NULL);
	while (tq)
	{
		if (tq->q == 0 || tq->q == 2)
		{
			ts = tq->qs;
			tq->qs = ms_strexp(sh, tq->qs);
			ft_free(ts);
			if (tq->q == 0)
				ms_wordsplit_q(ar, &tq);
		}
		tq = tq->nxq;
	}
	return (ms_join_quo(ar));
}
