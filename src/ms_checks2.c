/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:31:12 by jsala             #+#    #+#             */
/*   Updated: 2024/04/05 11:13:42 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
A character that, when unquoted, separates words.
A metacharacter is a space, tab, newline,
or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
*/
int	ft_ismeta(char c)
{
	return (ft_isspace(c) || (ft_isop(c) && !ft_isvarop(c))
		|| ft_islogic(c) || c == ';');
}

/* Checks if the argument is an assignment */
int	ft_isassign(char *s)
{
	if (!s)
		return (0);
	while (*s && ft_isalnum(*s))
		s++;
	if (*s == '=')
		return (1);
	return (0);
}

/* Checks if the current command is a built-in or not */
int	ft_isbuiltin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
