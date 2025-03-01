/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:34:27 by jsala             #+#    #+#             */
/*   Updated: 2024/05/19 11:39:23 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Manages the new output redirection > */
int	ms_redirect(t_shell *sh, t_cmd *c, t_arg *a)
{
	char	*pre_a;

	if (!a)
		return (0);
	pre_a = ft_strdup(a->ars);
	if (!pre_a || !ms_redir_exp(sh, a))
		return (EXIT_FAILURE);
	if (!a->ars[0])
		ms_errorf("minishell", AMBREDIR, pre_a, NULL);
	ft_free(pre_a);
	if (!a->ars[0])
		return (EXIT_FAILURE);
	ms_redir_quo(a);
	if (c->fdout > 0)
		close(c->fdout);
	c->fdout = open(a->ars, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (c->fdout > 0)
		return (EXIT_SUCCESS);
	ms_error(a->ars, ": ", strerror(errno), 1);
	return (EXIT_FAILURE);
}

/* Manages the append output redirection >> */
int	ms_aredirect(t_shell *sh, t_cmd *c, t_arg *a)
{
	char	*pre_a;

	if (!a)
		return (0);
	pre_a = ft_strdup(a->ars);
	if (!pre_a || !ms_redir_exp(sh, a))
		return (EXIT_FAILURE);
	if (!a->ars[0])
		ms_errorf("minishell", AMBREDIR, pre_a, NULL);
	ft_free(pre_a);
	if (!a->ars[0])
		return (EXIT_FAILURE);
	ms_redir_quo(a);
	if (c->fdout > 0)
		close(c->fdout);
	c->fdout = open(a->ars, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (c->fdout > 0)
		return (EXIT_SUCCESS);
	ms_error(a->ars, ": ", strerror(errno), 1);
	return (EXIT_FAILURE);
}

/* Manages the simple input redirection < */
int	ms_inredirect(t_shell *sh, t_cmd *c, t_arg *a)
{
	char	*pre_a;

	if (!a)
		return (0);
	pre_a = ft_strdup(a->ars);
	if (!pre_a || !ms_redir_exp(sh, a))
		return (EXIT_FAILURE);
	if (!a->ars[0])
		ms_errorf("minishell", AMBREDIR, pre_a, NULL);
	ft_free(pre_a);
	if (!a->ars[0])
		return (EXIT_FAILURE);
	ms_redir_quo(a);
	if (c->fdin > 0)
		close(c->fdin);
	c->fdin = open(a->ars, O_RDONLY);
	if (c->fdin > 0)
		return (EXIT_SUCCESS);
	ms_error(a->ars, ": ", strerror(errno), 1);
	return (EXIT_FAILURE);
}

t_arg	*ms_nxt_arg(t_arg *ta)
{
	if (ta->redir)
		ta = ta->nxa;
	ta = ta->nxa;
	return (ta);
}

/* Receives:
- the command to set the necessary redirections
- the current argument in the form of the text itself
*/
int	ms_redir(t_shell *sh, t_cmd *c)
{
	t_cmd	*tc;
	t_arg	*ta;

	tc = c;
	while (tc)
	{
		ta = tc->arl;
		c->redirerror = 0;
		while (ta && !c->redirerror)
		{
			if (ta->redir && !ft_strcmp(ta->ars, ">"))
				c->redirerror = ms_redirect(sh, tc, ta->nxa);
			else if (ta->redir && !ft_strcmp(ta->ars, ">>"))
				c->redirerror = ms_aredirect(sh, tc, ta->nxa);
			else if (ta->redir && !ft_strcmp(ta->ars, "<"))
				c->redirerror = ms_inredirect(sh, tc, ta->nxa);
			else if (ta->redir && !ft_strcmp(ta->ars, "<<"))
				c->redirerror = ms_heredoc(sh, tc, ta->nxa);
			ta = ms_nxt_arg(ta);
		}
		if (c->redirerror)
			tc->cmd = ft_free(tc->cmd);
		tc = tc->nxc;
	}
	return (sh->exitst);
}
