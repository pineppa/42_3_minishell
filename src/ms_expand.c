/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:54:50 by jsala             #+#    #+#             */
/*   Updated: 2024/05/18 01:48:15 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_assign_cmd(t_cmd *c, t_arg **pna, t_arg *ta)
{
	c->cmd = ta->ars;
	ta->ars = NULL;
	c->builtin = ft_isbuiltin(c->cmd);
	*pna = ta->nxa;
	ms_free_quolst(ta->aq);
	ft_free(ta);
}

// Choose command to execute: the first not redir arg
void	ms_choose_cmd(t_cmd *c)
{
	t_arg	*ta;
	t_arg	**pna;
	int		redir;

	while (c)
	{
		redir = 0;
		ta = c->arl;
		pna = &c->arl;
		while (ta)
		{
			if (ta->redir)
				redir = 1;
			if (!redir)
			{
				ms_assign_cmd(c, pna, ta);
				break ;
			}
			redir = ta->redir;
			pna = &ta->nxa;
			ta = ta->nxa;
		}
		c = c->nxc;
	}
}

// Function to clear args after expansion, deleting null string ones
void	ms_clearargs(t_cmd *c)
{
	t_cmd	*tc;
	t_arg	*ta;
	t_arg	**pna;

	tc = c;
	while (tc)
	{
		ta = tc->arl;
		pna = &tc->arl;
		while (ta)
		{
			if (!ta->ars || !ta->ars[0])
			{
				ft_delarg(pna);
				ta = *pna;
			}
			else
			{
				pna = &ta->nxa;
				ta = ta->nxa;
			}
		}
		tc->cmd = ft_free(tc->cmd);
		tc = tc->nxc;
	}
}

t_cmd	*ms_exp_args(t_shell *sh, t_cmd *ic)
{
	t_arg	*tmp_a;
	int		redir;

	tmp_a = ic->arl;
	redir = 0;
	while (tmp_a && (tmp_a->ars || tmp_a->aq))
	{
		if (tmp_a->ars)
			tmp_a->redir = ft_isredir(tmp_a->ars[0]);
		if (tmp_a->redir)
			redir = 1;
		if (!redir)
		{
			tmp_a = ms_argexp(sh, tmp_a);
			if (!tmp_a)
			{
				ms_error(ic->cmd, ": ", "malloc error while expansion", 1);
				return (NULL);
			}
		}
		redir = tmp_a->redir;
		tmp_a = tmp_a->nxa;
	}
	return (ic);
}

// Do var expansion and word splitting of not redir args
// redir args are the marked with redir field and the next one
// sanityze guarantees that there is some arg after the redir operand
t_cmd	*ms_expansion(t_shell *sh, t_cmd *cmd)
{
	t_cmd	*tmp_c;

	tmp_c = cmd;
	while (tmp_c)
	{
		tmp_c = ms_exp_args(sh, tmp_c);
		if (!tmp_c)
			return (ms_free_cmds(&cmd));
		tmp_c = tmp_c->nxc;
	}
	return (cmd);
}
