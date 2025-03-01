/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:14:00 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/18 02:09:13 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// write string command to history file
// If there is some error just skip
int	ft_write_history(char *cmd, char *home)
{
	int		fd;
	char	*fn;

	if (home)
	{
		fn = ms_strjoin3(home, "/", FILE_HIST);
		if (fn == ft_free(home))
			return (1);
	}
	else
		fn = FILE_HIST;
	fd = open(fn, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (home)
		ft_free(fn);
	if (fd < 0)
		return (0);
	ft_putendl_fd(cmd, fd);
	close(fd);
	return (0);
}

// get_next_line plus final \n removal before adding to history
char	*ft_gnl_trim(int fd)
{
	char	*line;
	int		l;

	line = get_next_line(fd);
	if (!line)
		return (line);
	l = ft_strlen(line);
	if (l && line[l - 1] == '\n')
		line[l - 1] = '\0';
	return (line);
}

// add lines from history file to readline history
void	ms_add_history_lines(char *line, int fd)
{
	while (line)
	{
		add_history(line);
		ft_free(line);
		line = ft_gnl_trim(fd);
	}
}

// load history file into readline history
// If there is some problem it just skips
int	ft_load_history(char *home)
{
	int		fd;
	char	*fn;
	char	*line;

	if (home)
	{
		fn = ms_strjoin3(home, "/", FILE_HIST);
		if (fn == ft_free(home))
			return (0);
	}
	else
		fn = FILE_HIST;
	fd = open(fn, O_RDONLY | O_CREAT, 0666);
	if (home)
		ft_free(fn);
	if (fd < 0)
		return (0);
	line = ft_gnl_trim(fd);
	ms_add_history_lines(line, fd);
	close(fd);
	return (0);
}

// add command from readline to history and history file
int	ft_add_history(t_shell *sh, char *cmd)
{
	add_history(cmd);
	ft_write_history(cmd, ms_get_var(sh, "HOME"));
	return (0);
}
