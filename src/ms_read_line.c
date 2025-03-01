/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:23:05 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/19 01:02:23 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_read_line(t_shell *sh)
{
	char	*rs;

	if (sh->isatty)
	{
		rs = readline(sh->prompt);
		if (rs && *rs)
		{
			sh->exitst = 0;
			ft_add_history(sh, rs);
		}
	}
	else
	{
		rs = get_next_line(STDIN_FILENO);
		if (rs && *rs && rs[ft_strlen(rs) - 1] == '\n')
			rs[ft_strlen(rs) - 1] = '\0';
		if (rs && *rs)
			sh->exitst = 0;
	}
	return (rs);
}
