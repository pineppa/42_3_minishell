/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:12:08 by jsala             #+#    #+#             */
/*   Updated: 2024/05/16 16:07:58 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Receives a string from the output of split and separates it in:
- command;
- args;
- Checks if builtin
- Redirections and env_var are not processed here*/
t_cmd	*ms_new_cmd(char **s)
{
	t_cmd	*cmd;

	if (!s || *s == NULL)
		return (NULL);
	cmd = (t_cmd *) ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	while (*s && *s[0] != '|')
	{
		cmd->arl = ft_argadd_back(cmd->arl, ft_argnew(*s));
		s++;
	}
	return (cmd);
}

/// Add new command nc at the end of the command list *lc
// if *lc == NULL nc will be the 1st cmd in the list
void	ms_cmdadd_back(t_cmd **lc, t_cmd *nc)
{
	t_cmd	*c;

	if (lc)
	{
		if (*lc)
		{
			c = *lc;
			while (c -> nxc)
				c = c -> nxc;
			c -> nxc = nc;
		}
		else
			*lc = nc;
	}
}

void	ft_freecmd(t_cmd **cmd)
{
	t_cmd	*temp;

	while (*cmd)
	{
		temp = *cmd;
		*cmd = (*cmd)->nxc;
		free(temp);
	}
}
