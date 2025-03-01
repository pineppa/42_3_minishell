/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:41:58 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/15 23:33:55 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*ms_nxtsortedvar(t_vars *pv, t_vars *ev)
{
	t_vars	*iv;
	t_vars	*minv;

	if (!ev)
		return (ev);
	iv = ev;
	minv = NULL;
	while (iv)
	{
		if ((!minv && pv && ft_strcmp(iv->name, pv->name) > 0)
			|| (!minv && !pv))
			minv = iv;
		else if (minv && ft_strcmp(iv->name, minv->name) < 0)
		{
			if (!pv)
				minv = iv;
			else if (ft_strcmp(iv->name, pv->name) > 0)
				minv = iv;
		}
		iv = iv->next;
	}
	return (minv);
}

int	ms_export_list(t_shell *sh, t_cmd *c)
{
	t_vars	*ev;

	c->fdin += 0;
	ev = ms_nxtsortedvar(NULL, sh->env);
	while (ev)
	{
		if (printf("declare -x %s", ev->name) < 0)
			return (1);
		if (ev->value)
		{
			if (printf("=\"%s\"", ev->value) < 0)
				return (1);
		}
		if (printf("\n") < 0)
			return (1);
		ev = ms_nxtsortedvar(ev, sh->env);
	}
	return (0);
}

int	xp_split_var(t_shell *sh, char *s, t_vars **v)
{
	char	*name;
	char	*value;

	*v = NULL;
	value = ft_strchr(s, '=');
	if (!value)
	{
		name = ft_strdup(s);
		value = ms_get_var(sh, name);
	}
	else
	{
		name = ft_substr(s, 0, ft_strlen(s) - ft_strlen(value));
		value = ft_substr(value, 1, ft_strlen(value) - 1);
	}
	*v = ms_new_var(name, value);
	return (ms_check_varname(name));
}

int	ms_export(t_shell *sh, t_cmd *c)
{
	t_vars	*v;
	int		i;

	i = 1;
	if (!c->ara[1])
		return (ms_export_list(sh, c));
	while (c->ara[i])
	{
		if (xp_split_var(sh, c->ara[i], &v))
		{
			ms_error("export: `", v->name, "': not a valid identifier", 1);
			v->name = ft_free(v->name);
			v->value = ft_free(v->value);
			v = ft_free(v);
		}
		else
		{
			ms_rm_var(sh, v->name);
			ms_add_var(&sh->env, v);
		}
		i++;
	}
	return (0);
}

int	ms_unset(t_shell *sh, t_cmd *c)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (c->ara[i])
	{
		if (ms_check_varname(c->ara[i]))
		{
			err = 1;
			ms_error("unset: `", c->ara[i], "': not a valid identifier", 1);
		}
		else
			ms_rm_var(sh, c->ara[i]);
		i++;
	}
	return (err);
}
