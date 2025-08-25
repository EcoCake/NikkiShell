/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:30:06 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/25 13:32:57 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*extract_quoted_str(const char *line, int *position, char quote)
{
	int		start;
	int		len;
	char	*extracted_line;

	start = (*position) - 1;
	len = 1;
	while (line[*position] && line[*position] != quote)
	{
		len++;
		(*position)++;
	}
	if (line[*position] != quote)
	{
		printf("Error, Unclosed quote '%c'\n", quote);
		return (NULL);
	}
	len++;
	(*position)++;
	extracted_line = ft_substr(line, start, len);
	return (extracted_line);
}

char	*extract_file_delimiter(const char *line, int *position)
{
	char	*extracted_value;
	char	quote;

	extracted_value = NULL;
	*position = skip_space(line, *position);
	if (!line[*position])
	{
		printf("Error, No filename after redirection\n");
		return (NULL);
	}
	if (is_quote(line[*position]))
	{
		quote = line[*position];
		(*position)++;
		extracted_value = extract_quoted_str(line, position, quote);
	}
	else
		extracted_value = extract_word(line, position);
	return (extracted_value);
}
