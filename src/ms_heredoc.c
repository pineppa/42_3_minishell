/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:09:10 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/18 10:48:01 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_hd_handler(int sig)
{
	(void) sig;
	g_ctrlc = 1;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

int	ft_chk_delimiter(char *eof)
{
	if (*eof == '|' || *eof == '>' || *eof == '<')
	{
		ms_error("syntax error near unexpected token `", eof, "'", 1);
		return (0);
	}
	return (0);
}

// check error or get delimiter after removing quotes
char	*ms_get_delimiter(char *eof)
{
	int		i;
	int		j;
	int		q;

	i = 0;
	j = 0;
	q = 0;
	while (eof[i])
	{
		if ((eof[i] == '"' && q != 1) || (eof[i] == '\'' && q != 2))
		{
			q = (q == 0) * (1 + (eof[i] == '"'));
			i++;
		}
		else
			eof[j++] = eof[i++];
	}
	eof[j] = '\0';
	return (eof);
}

char	*ms_heredoc_nl(char *line, char *eof, int pp[2])
{
	while (line && ft_strcmp(line, eof) && !g_ctrlc)
	{
		if (write(pp[1], line, ft_strlen(line)) == -1
			|| write(pp[1], "\n", 1) == -1)
		{
			printf("Error writing on stdout");
			return (NULL);
		}
		ft_free(line);
		line = readline("> ");
	}
	return (line);
}

// Expected associated command (c) and t_arg (ta) following <<
// eof = "<", ">" or "|" if this chars are just after <<
// eof = NULL if << and no word and end of line
int	ms_heredoc(t_shell *sh, t_cmd *c, t_arg *a)
{
	int		pp[2];
	char	*eof;
	char	*line;

	sh->exitst += 0;
	eof = ms_get_delimiter(a->ars);
	if (pipe(pp))
		return (1);
	g_ctrlc = 0;
	signal(SIGINT, sigint_hd_handler);
	line = readline("> ");
	line = ms_heredoc_nl(line, eof, pp);
	set_sighandlers();
	close(pp[1]);
	if (c->fdin)
		close(c->fdin);
	c->fdin = pp[0];
	ft_free(line);
	return (g_ctrlc);
}
