/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:43:52 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/18 00:12:45 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getredirtoken(char **st)
{
	int		i;
	char	*rs;

	i = 1 + (((*st)[0] == (*st)[1]));
	rs = ft_substr(*st, 0, i);
	*st = *st + i;
	if (!rs)
		*st = NULL;
	return (rs);
}

// Gets next token, between non quoted spaces or redirs, 
// in str *st moving the pointer of the string
char	*ms_nexttoken(char **st)
{
	char	*rs;
	int		i;
	int		q;

	while (**st && ft_isspace(**st))
		(*st)++;
	if (ft_isredir(**st))
		return (ms_getredirtoken(st));
	i = 0;
	q = 0;
	rs = *st;
	while (**st && (q || (!ft_isspace(**st) && !ft_isredir(**st))))
	{
		if ((**st == '"' && q != 1) || (**st == '\'' && q != 2))
			q = (q == 0) * (1 + (**st == '"'));
		i++;
		(*st)++;
	}
	while (**st && ft_isspace(**st))
		(*st)++;
	rs = ft_substr(rs, 0, i);
	if (!rs)
		*st = NULL;
	return (rs);
}

// split cmd string into args
// in case of error returns NULL and cmd list is freed
t_cmd	*ms_argsplit(t_cmd *c)
{
	t_cmd	*tc;
	t_arg	*ta;
	char	*ts;

	tc = c;
	while (tc)
	{
		ts = tc->cmd;
		while (ts && *ts)
		{
			ta = ft_argnew(ms_nexttoken(&ts));
			if (!ta || !ts)
			{
				ms_error(tc->cmd, ": ", "malloc error at argsplit", 1);
				return (ms_free_cmds(&c));
			}
			tc->arl = ft_argadd_back(tc->arl, ta);
		}
		tc = tc->nxc;
	}
	return (c);
}

char	*ms_nextcmd(char **cl)
{
	char	*st;
	char	*rs;
	int		q;

	q = 0;
	st = *cl;
	while (**cl && (q || **cl != '|' ))
	{
		if ((**cl == '"' && q != 1) || (**cl == '\'' && q != 2))
			q = (q == 0) * (1 + (**cl == '"'));
		(*cl)++;
	}
	rs = ft_substr(st, 0, *cl - st);
	if (!rs)
		ms_error(st, ": ", "malloc error", 1);
	return (rs);
}

// split the original command line cl into t_cmd structures
// in each there is the str between pipes in the cmd field
t_cmd	*ms_split_cmd(char *cl)
{
	t_cmd	*tc;
	t_cmd	*rc;

	rc = NULL;
	while (*cl && ft_isspace(*cl))
		cl++;
	while (*cl)
	{
		tc = ft_calloc(1, sizeof(t_cmd));
		if (!tc)
		{
			ms_error(cl, ": ", "malloc error", 1);
			return (ms_free_cmds(&rc));
		}
		cl += (rc && *cl == '|');
		ms_cmdadd_back(&rc, tc);
		tc->cmd = ms_nextcmd(&cl);
		if (!tc->cmd)
			return (ms_free_cmds(&rc));
	}
	return (rc);
}
