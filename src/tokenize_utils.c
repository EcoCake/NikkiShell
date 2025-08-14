/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:45:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/07/25 01:50:50 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	skip_space(const char *line, int i)
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
    return !(is_space(c) || is_operator(c) || is_quote(c) || c == '\0');
}

int is_word(const char *s)
{
	if (s && *s && !is_space(*s) && !is_quote(*s)
		&& *s != '$' && !is_operator(*s))
		return (1);
	return (0);
}

//this shit needs to be freed afterwards GOTTA REMEMBER I HATE THIS SHIT
char *extract_word(const char *line, int *position)
{
	int start;
	int len;
	len = 0;
	start = *position;

	while (line[*position] && is_word_char(line[*position]))
	{
		len++;
		(*position)++;
	}
	if (len == 0)
		return NULL;
	return (ft_substr(line, start, len));
}
//also hafta manually free this shit GOTTA REMEMBER
char *extract_quoted_str(const char *line, int *position, char quote)
{
	int start;
	int len;
	char *extracted_line;
	len = 0;
	start = *position;

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
	extracted_line = ft_substr(line, start, len);
	(*position)++;
	return (extracted_line);	
}

char *extract_file_delimiter(const char *line, int *position)
{
	char *extracted_value;
	char quote;
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