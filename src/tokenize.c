/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:00 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/25 13:39:57 by amezoe           ###   ########.fr       */
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

t_token	*tokenize(char *line)
{
	t_token				*head;
	t_token				*current;
	t_tokenize_context	context;

	head = NULL;
	current = NULL;
	if (!init_tokenize_context(&context, &head, &current, line))
		return (NULL);
	while (context.line[*(context.i)])
	{
		*(context.i) = skip_space(context.line, *(context.i));
		if (!context.line[*(context.i)])
			break ;
		if (!(handle_redir_heredoc(&context) || handle_pipe(&context)
				|| handle_quotes_words(&context)))
		{
			fprintf(stderr, "unknown token\n");
			free_token_list(head);
			head = NULL;
			break ;
		}
	}
	free(context.i);
	return (head);
}

int	handle_redir_heredoc(t_tokenize_context *context)
{
	if (context->line[*(context->i)] == '<'
		&& context->line[*(context->i) + 1] == '<')
		return (process_token(context, "<<", HERE_DOC, 2));
	else if (context->line[*(context->i)] == '>'
		&& context->line[*(context->i) + 1] == '>')
		return (process_token(context, ">>", REDIR_APPEND, 2));
	else if (context->line[*(context->i)] == '<')
		return (process_token(context, "<", REDIR_IN, 1));
	else if (context->line[*(context->i)] == '>')
		return (process_token(context, ">", REDIR_OUT, 1));
	return (0);
}

int	process_token(t_tokenize_context *context, char *token_str,
		t_token_types type, int len)
{
	char	*extracted_value;

	add_token(context->head, context->current, ft_strdup(token_str), type);
	*(context->i) += len;
	*(context->i) = skip_space(context->line, *(context->i));
	extracted_value = extract_word(context->line, context->i);
	if (!extracted_value)
	{
		fprintf(stderr,
			"syntax error near unexpected token 'newline' after '%s'\n",
			token_str);
		free_token_list(*(context->head));
		*(context->head) = NULL;
		return (0);
	}
	add_token(context->head, context->current, extracted_value, WORD);
	return (1);
}

int	handle_pipe(t_tokenize_context *context)
{
	if (context->line[*(context->i)] == '|')
	{
		add_token(context->head, context->current, ft_strdup("|"), PIPE);
		(*(context->i))++;
		return (1);
	}
	return (0);
}
