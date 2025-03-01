/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:32:24 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/15 23:26:40 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_set_env(t_shell *sh, char **envp)
{
	char	*name;
	char	*value;
	int		equal;
	t_vars	*rvar;

	while (*envp)
	{
		equal = ft_strchr(*envp, '=') - *envp;
		name = ft_substr(*envp, 0, equal);
		if (!name)
			return (1);
		value = ft_substr(*envp, equal + 1, ft_strlen(*envp) - equal - 1);
		if (!value)
			return (ft_free(name), 1);
		envp++;
		rvar = ms_new_var(name, value);
		if (!rvar)
			return (ft_free(name), ft_free(value), 1);
		ms_add_var(&sh->env, rvar);
	}
	return (0);
}

char	*ms_strjoin3(char const *s1, char const *s2, char const *s3)
{
	int		sz;
	char	*str;
	char	*tstr;

	sz = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = malloc(sizeof(char) * (sz + 1));
	if (str != NULL)
	{
		tstr = str;
		while (*s1)
			*tstr++ = *s1++;
		while (*s2)
			*tstr++ = *s2++;
		while (*s3)
			*tstr++ = *s3++;
		*tstr = '\0';
	}
	return (str);
}

int	ms_var_len(t_vars *var)
{
	int	i;

	i = 0;
	while (var)
	{
		if (var->value)
			i++;
		var = var->next;
	}
	return (i);
}

char	**ms_get_env(t_shell *sh)
{
	char	**renv;
	t_vars	*v;
	int		i;

	v = sh->env;
	renv = ft_calloc(ms_var_len(v) + 1, sizeof(char *));
	i = 0;
	while (renv && v)
	{
		if (v->value)
		{
			renv[i] = ms_strjoin3(v->name, "=", v->value);
			if (!renv[i])
				return (ms_free_strarr(renv));
			i++;
		}
		v = v->next;
	}
	return (renv);
}
