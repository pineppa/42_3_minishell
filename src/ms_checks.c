/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:23:35 by jsala             #+#    #+#             */
/*   Updated: 2024/04/03 18:01:13 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns 1 if the char is a redirect, otherwise 0
int	ft_isredir(char c)
{
	return (c == '<' || c == '>');
}

// Returns 1 if the char is a variable related character, otherwise 0
int	ft_isvarop(char c)
{
	return (c == '$' || c == '=');
}

// Returns 1 if the char is an operator, otherwise 0
int	ft_isop(char c)
{
	return (ft_isvarop(c) || c == '|' || ft_isredir(c));
}

/* 34 == " - 39 == ' */
int	ft_isquote(char c)
{
	return (c == 34 || c == 39);
}

int	ft_islogic(char c)
{
	return (c == '(' || c == ')' || c == '&' || c == '|');
}
