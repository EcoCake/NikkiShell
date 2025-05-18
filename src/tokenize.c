/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:00 by amezoe            #+#    #+#             */
/*   Updated: 2025/05/14 11:47:19 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token_types	t_type(const char *str)
{
	if (str[0] == '|')
		return (PIPE);
	else if (str[0] == '\'')
		return (QUOTE);
	else if (str[0] == '"')
		return (D_QUOTE);
	else if (str[0] == '<')
		return (REDIR_IN);
	else if (str[0] == '>')
		return (REDIR_OUT);
	else if (str[0] == '>' &&  str[1] == '>')
		return (REDIR_APPEND);
	else if (str[0] == '<' && str[1] == '<')
		return (HERE_DOC);
	else if (is_word(str))
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



