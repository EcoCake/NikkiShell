/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:00 by amezoe            #+#    #+#             */
/*   Updated: 2025/05/26 14:11:20 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

t_token_types   t_type(const char *str)
{
	if (!str || !*str)
		return (WORD);
	if (str[0] == '<' && str[1] == '<')
		return (HERE_DOC);
	else if (str[0] == '>' &&  str[1] == '>')
		return (REDIR_APPEND);
	else if (str[0] == '|')
		return (PIPE);
	else if (str[0] == '\'')
		return (QUOTE);
	else if (str[0] == '"')
		return (D_QUOTE);
	else if (str[0] == '<')
		return (REDIR_IN);
	else if (str[0] == '>')
		return (REDIR_OUT);
	else if (is_word(str))
		return (WORD);
	return (WORD);
}

void add_token(t_token **head, t_token **current, char *value, t_token_types type)
{
	t_token	*new_token;
	new_token = malloc(sizeof(t_token));

	if (!new_token)
			return;
    new_token->value = value;
    new_token->type = type;
    new_token->next = NULL;
    if (!*head)
    {
        *head = new_token;
        *current = new_token;
    }
    else
    {
        (*current)->next = new_token;
        *current = new_token;
    }
}

//im sorry this is ugly, i will refactor it later.

t_token *tokenize(char *line)
{
	t_token *head = NULL;
	t_token *current = NULL;
	char quote_char;
	int i;
	char *extracted_value;
	t_token_types token_type;
	i = 0;

	if (!line)
		return(NULL);
	while (line[i])
	{
		i = skip_space(line, i);
		if (!line[i])
			break;
		token_type = DEFAULT_ERROR;
		extracted_value = NULL;
		
		if (line[i] == '<' && line[i+1] == '<')
		{
			token_type = HERE_DOC;
			i += 2;
			extracted_value = extract_file_delimiter(line, &i);
		}
		
		else if (line[i] == '>' && line[i+1] == '>')
		{
		token_type = REDIR_APPEND;
		i += 2;
		extracted_value = extract_file_delimiter(line, &i);	
		}
		
		else if (line[i] == '<')
		{
		token_type = REDIR_IN;
		i += 1;
		extracted_value = extract_file_delimiter(line, &i);	
		}
		
		else if (line[i] == '>')
		{
		token_type = REDIR_OUT;
		i += 1;
		extracted_value = extract_file_delimiter(line, &i);	
		}
		
		else if (line[i] == '|')
		{
		token_type = PIPE;
		extracted_value = ft_strdup("|");
		i += 1;	
		}

		else if (is_quote(line[i]))
		{
			quote_char = line[i];
			i++;
			extracted_value = extract_quoted_str(line, &i, quote_char);
			if (quote_char == '\'')
				token_type = QUOTE;
			else
				token_type = D_QUOTE;
		}
		else
		{
			token_type = WORD;
			extracted_value = extract_word(line, &i);
		}
		
		if (token_type == DEFAULT_ERROR || extracted_value == NULL)
		{
			free_token_list(head);
			return NULL;
		}
		add_token(&head, &current, extracted_value, token_type);
	}
	return (head);
}

