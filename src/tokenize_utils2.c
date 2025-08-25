/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:39:39 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/25 13:39:43 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **head, t_token **current,
					char *value, t_token_types type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
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

int	init_tokenize_context(t_tokenize_context *context, t_token **head,
							t_token **current, char *line)
{
	if (!line)
		return (0);
	context->head = head;
	context->current = current;
	context->line = line;
	context->i = (int *)ft_calloc(1, sizeof(int));
	if (!context->i)
		return (0);
	return (1);
}

int	handle_quoted_str(t_tokenize_context *context)
{
	char	*extracted_value;

	extracted_value = extract_quoted_str(context->line, context->i,
			context->line[*(context->i)]);
	if (!extracted_value)
	{
		fprintf(stderr, "syntax error: unclosed quote\n");
		free_token_list(*(context->head));
		*(context->head) = NULL;
		return (0);
	}
	add_token(context->head, context->current, extracted_value, WORD);
	return (1);
}

int	handle_word(t_tokenize_context *context)
{
	char	*extracted_value;

	extracted_value = extract_word(context->line, context->i);
	if (!extracted_value)
	{
		fprintf(stderr, "malloc failure for word.\n");
		free_token_list(*(context->head));
		*(context->head) = NULL;
		return (0);
	}
	add_token(context->head, context->current, extracted_value, WORD);
	return (1);
}

int	handle_quotes_words(t_tokenize_context *context)
{
	if (is_quote(context->line[*(context->i)]))
		return (handle_quoted_str(context));
	else
		return (handle_word(context));
}
