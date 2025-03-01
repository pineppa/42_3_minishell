/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:20:14 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/19 14:57:03 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print current pwd
// ignore any argument
int	ms_pwd(t_shell *sh, t_cmd *c)
{
	char	*pwd;

	c->fdin += 0;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (sh && !pwd)
	{
		ms_error("pwd: ", strerror(errno), NULL, 1);
		return (EXIT_FAILURE);
	}
	if (printf("%s\n", pwd) < 0)
	{
		ft_free(pwd);
		return (EXIT_FAILURE);
	}
	ft_free(pwd);
	return (EXIT_SUCCESS);
}

int	ms_cd(t_shell *sh, t_cmd *c)
{
	char	*nd;
	char	*em;

	if (sh && !c->ara[1])
	{
		nd = ms_get_var(sh, "HOME");
		if (!nd)
			return (1 + ms_error("cd: HOME not set", NULL, NULL, 1));
	}
	else
		nd = c->ara[1];
	if (chdir(nd))
	{
		em = ft_strjoin(": ", strerror(errno));
		if (!em)
			return (1);
		ms_error("cd: ", nd, em, 1);
		ft_free(em);
		if (!c->ara[1])
			ft_free(nd);
		return (EXIT_FAILURE);
	}
	if (!c->ara[1])
		ft_free(nd);
	return (EXIT_SUCCESS);
}

int	ms_echo_new_line(t_shell *sh, t_cmd *c, int i)
{
	size_t	j;

	j = 0;
	if (sh && c->ara[i] && c->ara[i][j] == '-')
	{
		j++;
		while (c->ara[i][j] == 'n')
			j++;
		if (j == ft_strlen(c->ara[i]))
			return (1);
	}
	return (0);
}

int	ms_echo(t_shell *sh, t_cmd *c)
{
	int		nl;
	int		i;

	i = 1;
	nl = ms_echo_new_line(sh, c, i);
	if (nl)
		i++;
	while (c->ara[i])
	{
		if (nl && ms_echo_new_line(sh, c, i))
		{
			i++;
			continue ;
		}
		if (write(1, c->ara[i], ft_strlen(c->ara[i])) == -1)
			return (1);
		i++;
		if (c->ara[i])
			if (write(1, " ", 1) == -1)
				return (1);
	}
	if (!nl)
		if (write(1, "\n", 1) == -1)
			return (1);
	return (0);
}
