/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:45:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/26 20:06:29 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		return NULL;
	}	
	len++; 
	(*position)++; 
	extracted_line = ft_substr(line, start, len);
	return (extracted_line);
}

char *extract_file_delimiter(const char *line, int *position)
{
	char	*extracted_value;
	char	quote;

	extracted_value = NULL;
	*position = skip_space(line, *position);
	if (!line[*position])
	{
		printf("Error, No filename after redirection\n");
		return NULL;
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
