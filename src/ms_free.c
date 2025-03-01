/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:37:42 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/19 11:17:58 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_free_allvars(t_vars **vars)
{
	if (*vars && (*vars)->next)
		ms_free_allvars(&(*vars)->next);
	if (*vars)
	{
		(*vars)->name = ft_free((*vars)->name);
		(*vars)->value = ft_free((*vars)->value);
		*vars = ft_free(*vars);
	}
	return (0);
}

// Free all args in list recursively
t_arg	*ms_free_args(t_arg *ar)
{
	if (ar && ar->nxa)
		ar->nxa = ms_free_args(ar->nxa);
	if (ar)
	{
		ms_free_quolst(ar->aq);
		ar->ars = ft_free(ar->ars);
		ar = ft_free(ar);
	}
	return (ar);
}

t_cmd	*ms_free_cmds(t_cmd **c)
{
	if (*c && (*c)->nxc)
		ms_free_cmds(&(*c)->nxc);
	if (*c)
	{
		if ((*c)->cmd)
			(*c)->cmd = ft_free((*c)->cmd);
		if ((*c)->arl)
			(*c)->arl = ms_free_args((*c)->arl);
		if ((*c)->ara)
		{
			(*c)->ara[0] = ft_free((*c)->ara[0]);
			(*c)->ara = ft_free((*c)->ara);
		}
		*c = ft_free(*c);
	}
	return (NULL);
}

void	*ms_free_strarr(char **sta)
{
	int	i;

	i = 0;
	while (sta && sta[i])
	{
		sta[i] = ft_free(sta[i]);
		i++;
	}
	return (ft_free(sta));
}

int	ms_free(t_shell *sh, t_cmd **c, char **sta)
{
	if (sh)
	{
		ms_free_allvars(&sh->env);
		ms_free_allvars(&sh->vars);
	}
	if (c)
		ms_free_cmds(c);
	if (sta)
		ms_free_strarr(sta);
	return (0);
}
