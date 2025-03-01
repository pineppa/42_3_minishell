/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:43:30 by josegar2          #+#    #+#             */
/*   Updated: 2024/01/11 11:49:53 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_count(char const *str, char c)
{
	int	cw;

	cw = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			cw++;
		while (*str && *str != c)
			str++;
	}
	return (cw);
}

static int	next_word(const char **pstr, char c)
{
	const char	*auxs;
	int			lw;

	lw = 0;
	while (**pstr && **pstr == c)
		*pstr = *pstr + 1;
	auxs = *pstr;
	while (**pstr && **pstr != c)
	{
		lw++;
		*pstr = *pstr + 1;
	}
	*pstr = auxs;
	return (lw);
}

static char	**free_strs(char **strs)
{
	int	n;

	n = 0;
	while (strs[n])
	{
		free(strs[n]);
		n++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		n_str;
	int		l_str;
	char	**strs;

	if (!s)
		return (NULL);
	n_str = word_count(s, c);
	strs = (char **) malloc((n_str + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs[n_str] = NULL;
	n_str = 0;
	while (*s)
	{
		l_str = next_word(&s, c);
		if (l_str)
		{
			strs[n_str] = ft_substr(s, 0, l_str);
			if (! strs[n_str++])
				return (free_strs(strs));
			s = s + l_str;
		}
	}
	return (strs);
}
