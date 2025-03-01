/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:50:58 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/15 23:50:09 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sanitize_pipe(char *cmd, int i)
{
	if (i == 0)
	{
		ms_errorf("minishell", SYNERRNUNEXP, "|", NULL);
		return (-1);
	}
	while (cmd[++i] && ft_isspace(cmd[i]))
		;
	if (cmd[i] == '\0' || cmd[i] == '|' || cmd[i] == '\n')
	{
		if (cmd[i] == '\0')
			ms_errorf("minishell", SYNEOF, NULL, NULL);
		else if (cmd[i] == '|')
			ms_errorf("minishell", SYNERRNUNEXP, "|", NULL);
		else if (cmd[i] == '\n')
			ms_errorf("minishell", SYNERRNUNEXP, "\n", NULL);
		return (-1);
	}
	return (i);
}

int	ft_sanitize_redir(char *cmd, int i)
{
	i += (cmd[i] == cmd[i + 1]);
	while (cmd[++i] && ft_isspace(cmd[i]))
		;
	if (ft_isredir(cmd[i]) || cmd[i] == '|' || cmd[i] == '\n' || cmd[i] == '\0')
	{
		if (cmd[i] == '\0')
			ms_errorf("minishell", SYNERRNUNEXP, "newline", NULL);
		else if (cmd[i] == '|')
			ms_errorf("minishell", SYNERRNUNEXP, "|", NULL);
		else if (ft_isredir(cmd[i]) && (cmd[i] == cmd[i + 1]))
		{
			if (cmd[i] == '>')
				ms_errorf("minishell", SYNERRNUNEXP, ">>", NULL);
			else if (cmd[i] == '<')
				ms_errorf("minishell", SYNERRNUNEXP, "<<", NULL);
		}
		else if (cmd[i] == '>')
			ms_errorf("minishell", SYNERRNUNEXP, ">", NULL);
		else if (cmd[i] == '<')
			ms_errorf("minishell", SYNERRNUNEXP, "<", NULL);
		return (-1);
	}
	return (i);
}

char	*ft_sigcheck(char *cmd, int sig_quote)
{
	if (sig_quote)
	{
		if (sig_quote == 1)
			ms_errorf("minishell", NOCLOSE, "'", cmd);
		else
			ms_errorf("minishell", NOCLOSE, "\"", cmd);
		return (ft_free(cmd));
	}
	return (cmd);
}

char	*ft_trimstr(char *cmd)
{
	char	*ts;

	ts = ft_strtrim(cmd, " \t\r\n\v\f");
	ft_free(cmd);
	return (ts);
}

/* Cycles through the input and sanitizes the input passed to it */
char	*ft_sanitize_cmd(char *cmd)
{
	int		i;
	int		sig_quote;

	i = 0;
	sig_quote = 0;
	cmd = ft_trimstr(cmd);
	if (!cmd)
		return (cmd);
	while (cmd[i])
	{
		if (!sig_quote && cmd[i] == '#')
			break ;
		if (ft_isquote(cmd[i]))
			ms_sig_quote(cmd[i++], &sig_quote);
		else if (!sig_quote && cmd[i] == '|')
			i = ft_sanitize_pipe(cmd, i);
		else if (!sig_quote && ft_isredir(cmd[i]))
			i = ft_sanitize_redir(cmd, i);
		else
			i++;
		if (i == -1)
			return (ft_free(cmd));
	}
	return (ft_sigcheck(cmd, sig_quote));
}
