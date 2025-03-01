/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:09:48 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/17 00:32:20 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exitcode(t_cmd *c)
{
	int		exc;
	long	lcode;

	exc = 0;
	if (c->ara && c->ara[1])
	{
		if (ft_atol_ms(c->ara[1], &lcode))
		{
			exc = -1;
			ms_error("exit: ", c->ara[1], ": numeric argument required", 1);
		}
		else
			exc = lcode & 255;
	}
	if (exc >= 0 && c->ara && c->ara[1] && c->ara[2])
	{
		exc = -2;
		ms_error("exit: too many arguments", NULL, NULL, 1);
	}
	return (exc);
}

// exit [n]
// exit shell with code n (0-255 -> 8 lower bits of n)
// exit N other_arg ... -> doesn't exit, error message and return 1
// exit not_number -> exit shell with error message and code = 255
// exit not_number other_arg ... -> idem than previous one
// It just exits shell if not part of a pipe of commands
int	ms_exit(t_shell *sh, t_cmd *c)
{
	int		ecode;

	if (!c->nxc && !c->pp[0])
		ms_error("exit", NULL, NULL, 0);
	ecode = get_exitcode(c);
	if (!c->nxc && !c->pp[0] && ecode >= -1)
	{
		ms_free(sh, &c, NULL);
		if (ecode == -1)
			ecode = 255;
		exit (ecode);
	}
	ecode = 255 * (ecode == -1) + 1 *(ecode == -2) + ecode * (ecode >= 0);
	return (ecode);
}

// print environment variables to fdout (1 or redirection)
// There can be variables with value = NULL ==> not print
// It happens if "export TT" and TT doesn't exist
int	ms_env(t_shell *sh, t_cmd *c)
{
	t_vars	*ev;

	if (c->ara && c->ara[1])
	{
		ms_error("env: no arguments expected -- ", c->arl->ars, NULL, 0);
		return (EXIT_FAILURE);
	}
	ev = sh->env;
	while (ev)
	{
		if (ev->value)
		{
			if (printf("%s=%s\n", ev->name, ev->value) < 0)
			{
				ms_error("env: print error", NULL, NULL, 0);
				return (EXIT_FAILURE);
			}
		}
		ev = ev->next;
	}
	return (EXIT_SUCCESS);
}

int	ms_run_builtin(t_shell *sh, t_cmd *c)
{
	if (!c)
		return (0);
	if (!ft_strcmp(c->cmd, "echo"))
		return (ms_echo(sh, c));
	if (!ft_strcmp(c->cmd, "cd"))
		return (ms_cd(sh, c));
	if (!ft_strcmp(c->cmd, "pwd"))
		return (ms_pwd(sh, c));
	if (!ft_strcmp(c->cmd, "export"))
		return (ms_export(sh, c));
	if (!ft_strcmp(c->cmd, "unset"))
		return (ms_unset(sh, c));
	if (!ft_strcmp(c->cmd, "env"))
		return (ms_env(sh, c));
	if (!ft_strcmp(c->cmd, "exit"))
		return (ms_exit(sh, c));
	return (1);
}
