/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:52:52 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/13 16:58:20 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_path(char **path, t_cmd *c)
{
	DIR				*dir;
	struct dirent	*de;

	de = NULL;
	while (*path)
	{
		dir = opendir(*path);
		if (!dir)
		{
			path++;
			continue ;
		}
		de = readdir(dir);
		while (de && ft_strcmp(de->d_name, c->cmd))
			de = readdir(dir);
		closedir(dir);
		if (de)
			return (*path);
		path++;
	}
	return (NULL);
}

// If cmd string doesn't have / and is not builtin -> locate in PATH
int	ms_get_cmd(t_shell *sh, t_cmd *c)
{
	char	**path;
	char	*ts;
	char	*tc;

	path = NULL;
	ts = NULL;
	tc = NULL;
	if (ft_strchr(c->cmd, '/') || ft_isbuiltin(c->cmd))
		return (0);
	ts = ms_get_var(sh, "PATH");
	if (!ts)
		return (0);
	path = ft_split(ts, ':');
	ts = ft_free(ts);
	ts = ms_get_path(path, c);
	if (ts)
	{
		tc = c->cmd;
		c->cmd = ms_strjoin3(ts, "/", tc);
		ft_free(tc);
	}
	ms_free_strarr(path);
	return (0);
}
