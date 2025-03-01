/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:00:45 by jsala             #+#    #+#             */
/*   Updated: 2024/05/16 17:47:10 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ft_argnew(void *content)
{
	t_arg	*nar;

	nar = (t_arg *) malloc(sizeof(t_arg));
	if (!nar)
		return (NULL);
	nar->ars = content;
	nar->redir = 0;
	nar->aq = NULL;
	nar->nxa = NULL;
	return (nar);
}

/* Adds an argument to the end of the argument list */
t_arg	*ft_argadd_back(t_arg *arg, t_arg *new)
{
	t_arg	*temp;

	if (!new)
		return (NULL);
	if (!arg)
		return (new);
	temp = arg;
	while (temp->nxa)
		temp = temp->nxa;
	temp->nxa = new;
	return (arg);
}

/* Adds an argument to the beginning of the argument list */
t_arg	*ft_argadd_front(t_arg *arg, t_arg *new)
{
	if (!new)
		return (NULL);
	if (!arg)
		return (new);
	new->nxa = arg;
	return (new);
}

void	ft_delarg(t_arg **arg)
{
	t_arg	*temp;

	temp = *arg;
	if (!temp)
		return ;
	*arg = temp->nxa;
	ms_free_quolst(temp->aq);
	ft_free(temp->ars);
	ft_free(temp);
}

/*
* Insert t_arg structure just after the given t_arg
*/
t_arg	*ft_insarg_after(t_arg *where, t_arg *what)
{
	t_arg	*pnxa;

	if (!where || !what)
		return (NULL);
	pnxa = where->nxa;
	where->nxa = what;
	what->nxa = pnxa;
	return (what);
}
