/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:03:48 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/26 20:08:03 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	get_var_name_len(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '?' || s[i] == '$')
		return (1);
	while (s[i] && is_var_char(s[i]))
		i++;
	return (i);
}

int	is_word(const char *s)
{
	if (s && *s && !is_space(*s) && !is_quote(*s)
		&& *s != '$' && !is_operator(*s))
		return (1);
	return (0);
}

char	*extract_word(const char *line, int *position)
{
	int	start;
	int	len;

	len = 0;
	start = *position;
	while (line[*position] && is_word_char(line[*position]))
	{
		len++;
		(*position)++;
	}
	if (len == 0)
		return (NULL);
	return (ft_substr(line, start, len));
}

int	count_word_tokens(t_token *head)
{
	int	count;

	count = 0;
	while (head && head->type == WORD)
	{
		count++;
		head = head->next;
	}
	return (count);
}
