/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:59:47 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/19 00:53:47 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ctrlc;

// initialize shell
//	structure
//	signals
//	environment
//	load history from history file
//	backup of terminal settings to restore after each command
int	init_shell(t_shell *ts, char **envp)
{
	g_ctrlc = 0;
	ft_bzero(ts, sizeof(t_shell));
	ts->prompt = PROMPT;
	if (set_sighandlers())
		return (EXIT_FAILURE);
	if (ms_set_env(ts, envp))
		return (EXIT_FAILURE);
	if (ft_load_history(ms_get_var(ts, "HOME")) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ts->isatty = isatty(STDIN_FILENO);
	if (ts->isatty && tcgetattr(STDIN_FILENO, &ts->termios_backup) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// if sanityze has failed, read cmd again
char	*ms_read_cmd(char *cmd, t_shell **shdata)
{
	while (!cmd)
	{
		(*shdata)->lastst = 258;
		cmd = ms_read_line(*shdata);
		if (!cmd)
			return (NULL);
		cmd = ft_sanitize_cmd(cmd);
	}
	return (cmd);
}

void	ms_runcmd(char *cmd, t_shell *shdata, t_cmd *c)
{
	shdata->exitst = 0;
	cmd = ft_sanitize_cmd(cmd);
	c = ms_argsplit(ms_split_cmd(cmd));
	c = ms_expansion(shdata, c);
	ms_clearargs(c);
	ms_quote(c);
	ms_choose_cmd(c);
	shdata->exitst = ms_redir(shdata, c);
	if (c && !shdata->exitst)
		ms_fork_cmds(shdata, c);
	ms_free_cmds(&c);
	cmd = ft_free(cmd);
	shdata->lastst = shdata->exitst;
}

/* Loop of command execution with these steps
	- Sanityze cmd (unclosed quotes, redir without filename, ...)
	- If sanityze fails get new cmd
	- Split cmd string into a list of t_cmd
	- Split each t_cmd into a list of t_arg
	- Expand all t_arg, not the redir args
	- Remove args that become NULL or null strings after expansion
	- Remove quotes from args
	- Choose cmd from list of t_arg
	- Manage redirections and pipes
	- Launch commands
	- Free everything
*/
void	ms_run_cmds(char *cmd, t_shell *shdata, t_cmd *c)
{
	while (cmd)
	{
		cmd = ft_sanitize_cmd(cmd);
		cmd = ms_read_cmd(cmd, &shdata);
		if (!cmd)
			return ;
		c = ms_argsplit(ms_split_cmd(cmd));
		c = ms_expansion(shdata, c);
		ms_clearargs(c);
		ms_quote(c);
		ms_choose_cmd(c);
		shdata->exitst = ms_redir(shdata, c);
		if (c)
			ms_fork_cmds(shdata, c);
		ms_free_cmds(&c);
		cmd = ft_free(cmd);
		shdata->lastst = shdata->exitst;
		cmd = ms_read_line(shdata);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shdata;
	char	*cmd;
	t_cmd	*c;

	if (argc != 1 && !(argc == 3 && !ft_strcmp(argv[1], "-c")))
		return (printf("Option not supported\n"), EXIT_FAILURE);
	if (init_shell(&shdata, envp))
		return (EXIT_FAILURE);
	c = NULL;
	if (argc == 3 && !ft_strcmp(argv[1], "-c"))
		ms_runcmd(ft_strdup(argv[2]), &shdata, c);
	else
	{
		cmd = ms_read_line(&shdata);
		ms_run_cmds(cmd, &shdata, c);
		if (shdata.isatty)
			write(STDOUT_FILENO, "exit\n", 5);
	}
	ms_free(&shdata, &c, NULL);
	return (EXIT_SUCCESS);
}
