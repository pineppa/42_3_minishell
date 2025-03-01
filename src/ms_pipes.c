/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:44:39 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/19 11:27:03 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_set_pipes(t_cmd *c)
{
	t_cmd	*tc;

	if (!c)
		return (EXIT_SUCCESS);
	tc = c->nxc;
	while (tc)
	{
		if (pipe(tc->pp))
		{
			ms_error("pipe creation error", NULL, NULL, 1);
			return (EXIT_FAILURE);
		}
		tc = tc->nxc;
	}
	return (EXIT_SUCCESS);
}

int	ms_close_pipes(t_cmd *c)
{
	t_cmd	*tc;

	if (!c)
		return (0);
	tc = c;
	while (tc)
	{
		if (tc->pp[0] > 0)
			if (close(tc->pp[0]))
				return (1);
		if (tc->pp[1] > 0)
			if (close(tc->pp[1]))
				return (1);
		if (tc->fdin > 0 && tc->fdin != tc->pp[0])
			if (close(tc->fdin))
				return (1);
		if (tc->fdout > 1
			&& (!tc->nxc || (tc->nxc && tc->fdout != tc->nxc->pp[1])))
			if (close (tc->fdout))
				return (1);
		tc = tc->nxc;
	}
	return (0);
}
