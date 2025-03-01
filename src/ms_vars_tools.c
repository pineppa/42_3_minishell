/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:34:48 by josegar2          #+#    #+#             */
/*   Updated: 2024/04/19 10:44:08 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_update_var(t_vars *var, char *value)
{
	ft_free(var->value);
	var->value = value;
	return (0);
}

int	ms_free_var(t_vars **vl, t_vars *iv, t_vars *pv)
{
	if (pv == iv)
		*vl = iv->next;
	else
		pv->next = iv->next;
	iv->name = ft_free(iv->name);
	iv->value = ft_free(iv->value);
	iv = ft_free(iv);
	return (0);
}

int	ms_check_varname(char *name)
{
	if (!name || ft_isdigit(*name))
		return (1);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (1);
		name++;
	}
	return (0);
}

/* return the length of the varname that follows a $
	s must point to the character after a $ 
	if it returns 0 $ must be taken as a char
*/
int	ms_varname_len(char *s)
{
	int	i;

	if (!s || !*s || ft_isdigit(*s))
		return (0);
	if (*s == '?')
		return (1);
	i = 0;
	while (*s && (ft_isalnum(*s) || *s == '_'))
	{
		i++;
		s++;
	}
	return (i);
}

/* expand de $var and update the string pointer to the next position 
	if var doesn't exist returns null string
	Returned string mut be freed
*/
char	*ms_exp_var(t_shell *sh, char **s)
{
	int		l;
	char	*rs;
	char	*vn;

	if (!*s || **s != '$')
		return (NULL);
	l = ms_varname_len(++(*s));
	if (!l)
		return (ft_strdup("$"));
	vn = ft_substr(*s, 0, l);
	rs = ms_get_var(sh, vn);
	if (!rs)
		rs = ft_strdup("");
	ft_free(vn);
	*s += l;
	return (rs);
}
