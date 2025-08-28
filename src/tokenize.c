/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:00 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 18:27:59 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_types	t_type(const char *str)
{
	if (!str || !*str)
		return (WORD);
	if (str[0] == '<' && str[1] == '<')
		return (HERE_DOC);
	else if (str[0] == '>' && str[1] == '>')
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

void	add_token(t_token **head, t_token **curr, char *val, t_token_types type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = val;
	new_token->type = type;
	new_token->next = NULL;
	if (!*head)
	{
		*head = new_token;
		*curr = new_token;
	}
	else
	{
		(*curr)->next = new_token;
		*curr = new_token;
	}
}

t_token	*tokenize(char *line)
{
	t_tokenizer_state	state;

	if (!line)
		return (NULL);
	state.head = NULL;
	state.current = NULL;
	state.line = line;
	state.i = 0;
	if (!process_line(&state))
	{
		free_token_list(state.head);
		return (NULL);
	}
	return (state.head);
}
