/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.barcelona.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:58:41 by josegar2          #+#    #+#             */
/*   Updated: 2024/04/14 16:37:52 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_read_buffer(int fd, char **s)
{
	char	*buf;
	char	*ts;
	int		r;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	r = read(fd, buf, BUFFER_SIZE);
	if (r < 0)
		return (ft_free(buf), 2);
	buf[r] = '\0';
	ts = ft_strjoin(*s, buf);
	buf = ft_free(buf);
	*s = ft_free(*s);
	*s = ts;
	if (!ts)
		return (-3);
	if (r == 0 && **s == '\0')
	{
		*s = ft_free(*s);
		return (-4);
	}
	return (r == 0);
}

char	*ft_get_line(char **s, int fd)
{
	char	*nlp;
	int		eof;

	nlp = NULL;
	eof = 0;
	while (!eof && !nlp)
	{
		if (ft_strchr(*s, '\n'))
			return (ft_split_1nl(s));
		else
		{
			eof = ft_read_buffer(fd, s);
			if (eof < 0)
				return (NULL);
			if (eof)
			{
				nlp = *s;
				*s = NULL;
			}
		}
	}
	return (nlp);
}

char	*get_next_line(int fd)
{
	static char	*fc;
	char		*nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fc == NULL)
	{
		fc = malloc(sizeof(char));
		if (fc == NULL)
			return (fc);
		*fc = '\0';
	}
	nl = ft_get_line(&fc, fd);
	if (!nl && fc)
		fc = ft_free(fc);
	return (nl);
}
