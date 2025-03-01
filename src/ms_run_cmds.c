/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:50:15 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/19 11:41:12 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_just_builtin(t_shell *sh, t_cmd *c)
{
	int	oldfdin;
	int	oldfdout;

	if (!(c->cmd))
		return (sh->exitst);
	oldfdin = dup(STDIN_FILENO);
	oldfdout = dup(STDOUT_FILENO);
	if (ms_get_args(c))
		return (1 + ms_error(c->cmd, ": ", "malloc error", 1));
	if (c->fdin)
		dup2(c->fdin, STDIN_FILENO);
	if (c->fdout > 1)
		dup2(c->fdout, STDOUT_FILENO);
	ms_close_pipes(c);
	sh->exitst = ms_run_builtin(sh, c);
	if (c->fdin)
		dup2(oldfdin, STDIN_FILENO);
	if (c->fdout > 1)
		dup2(oldfdout, STDOUT_FILENO);
	close(oldfdin);
	close(oldfdout);
	return (sh->exitst);
}

void	ms_child_cmd(t_shell *sh, t_cmd *fc, t_cmd *c, char **env)
{
	if (ms_get_args(c))
		exit (1 + ms_error(c->cmd, ": ", "malloc error", 1));
	ms_get_cmd(sh, c);
	if (!c->fdin && (c->pp[0] || c->pp[1]))
		c->fdin = c->pp[0];
	if (c->nxc && c->fdout <= 1)
		c->fdout = c->nxc->pp[1];
	if (c->fdin)
		dup2(c->fdin, 0);
	if (c->fdout > 1)
		dup2(c->fdout, 1);
	ms_close_pipes(fc);
	if (c->builtin)
		exit(ms_run_builtin(sh, c));
	execve(c->cmd, c->ara, env);
	if (errno == ENOENT)
		exit (127 + ms_error(c->cmd, ": command not found", NULL, 1));
	if (errno == EACCES)
		exit (126 + ms_error(c->cmd, ": permision denied", NULL, 1));
	exit (errno + ms_error(c->cmd, ": ", strerror(errno), 1));
}

void	ms_launch_child(t_shell *sh, t_cmd *c, t_cmd *ic)
{
	int	redirerror;

	reset_sighandlers();
	if (ic->cmd)
		ms_child_cmd(sh, c, ic, sh->envar);
	else
	{
		redirerror = c->redirerror;
		ms_free(sh, &c, sh->envar);
		exit(redirerror);
	}
}

int	ms_wait_children(t_shell *sh, t_cmd *c, int nc, int lastpid)
{
	int		exitcd;

	exitcd = 0;
	ms_close_pipes(c);
	sh->envar = ms_free_strarr(sh->envar);
	signal(SIGINT, SIG_IGN);
	while (nc--)
		if (wait(&exitcd) == lastpid)
			sh->exitst = exitcd;
	if (sh->isatty)
		tcsetattr(STDIN_FILENO, TCSANOW, &sh->termios_backup);
	if (WIFEXITED(sh->exitst))
		sh->exitst = WEXITSTATUS(sh->exitst);
	else if (WIFSIGNALED(sh->exitst))
	{
		if (sh->exitst == 3)
			printf("Quit: 3\n");
		else
			printf("\n");
		sh->exitst = WTERMSIG(sh->exitst) + 128;
	}
	signal(SIGINT, sigint_handler);
	return (0);
}

int	ms_fork_cmds(t_shell *sh, t_cmd *c)
{
	t_cmd	*ic;
	int		pid;
	int		nc;

	if (c->builtin && !c->nxc)
		return (ms_just_builtin(sh, c));
	sh->envar = ms_get_env(sh);
	if (!sh->envar)
		return (1);
	ic = c;
	nc = 0;
	ms_set_pipes(c);
	while (ic)
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (!pid)
			ms_launch_child(sh, c, ic);
		ic = ic->nxc;
		nc++;
	}
	ms_wait_children(sh, c, nc, pid);
	return (0);
}
