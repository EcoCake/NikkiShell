/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:45:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/05/14 11:33:18 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	skip_space(char *line, int i)
{
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
int	is_word_char(char c)
{
	if (ft_isalnum(c) || c == '-'
		|| c == '_' || c == '.' || c == '/')
		return (1);
	return (0);
}

int is_word(const char *s)
{
	if (s && *s && !is_space(*s) && !is_quote(*s)
		&& *s != '$' && !is_operator(*s))
		return (1);
	return (0);
}
