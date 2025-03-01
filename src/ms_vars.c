/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:46:20 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/12 17:59:37 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// nm: name. string already created
// val: value. string already created
t_vars	*ms_new_var(char *nm, char *val)
{
	t_vars	*rvar;

	rvar = (t_vars *) ft_calloc(1, sizeof(t_vars));
	if (rvar)
	{
		rvar->name = nm;
		rvar->value = val;
	}
	return (rvar);
}

// it can be added to &sh->env or &sh->vars
t_vars	*ms_add_var(t_vars **vars, t_vars *var)
{
	t_vars	*tv;

	if (*vars)
	{
		tv = *vars;
		while (tv->next)
			tv = tv->next;
		tv->next = var;
	}
	else
		*vars = var;
	return (var);
}

// the return string must be freed after using it
char	*ms_get_var(t_shell *sh, char *name)
{
	t_vars	*ivar;

	if (!ft_strcmp(name, "?"))
		return (ft_itoa(sh->lastst));
	ivar = sh->env;
	while (ivar)
	{
		if (!ft_strcmp(name, ivar->name))
			return (ft_strdup(ivar->value));
		ivar = ivar->next;
	}
	ivar = sh->vars;
	while (ivar)
	{
		if (!ft_strcmp(name, ivar->name))
			return (ft_strdup(ivar->value));
		ivar = ivar->next;
	}
	return (NULL);
}

// previously call ms_check_varname
int	ms_rm_var(t_shell *sh, char *name)
{
	t_vars	*ivar;
	t_vars	*pvar;

	ivar = sh->env;
	pvar = sh->env;
	while (ivar)
	{
		if (!ft_strcmp(name, ivar->name))
			return (ms_free_var(&sh->env, ivar, pvar));
		pvar = ivar;
		ivar = ivar->next;
	}
	pvar = sh->vars;
	ivar = sh->vars;
	while (ivar)
	{
		if (!ft_strcmp(name, ivar->name))
			return (ms_free_var(&sh->vars, ivar, pvar));
		pvar = ivar;
		ivar = ivar->next;
	}
	return (0);
}

// previously call ms_check_varname
int	ms_set_var(t_shell *sh, char *name, char *value)
{
	t_vars	*ivar;

	ivar = sh->env;
	while (ivar)
	{
		if (ft_strcmp(name, ivar->name))
			return (ms_update_var(ivar, value));
		ivar = ivar->next;
	}
	ivar = sh->vars;
	while (ivar)
	{
		if (ft_strcmp(name, ivar->name))
			return (ms_update_var(ivar, value));
		ivar = ivar->next;
	}
	ivar = ms_new_var(name, value);
	if (!ivar)
		return (1);
	ms_add_var(&sh->vars, ivar);
	return (0);
}
