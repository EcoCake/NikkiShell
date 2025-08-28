/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:38:04 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 18:41:27 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_tokenize(int *i, char *line)
{
	if ((line[*i] == '<' && line[*i + 1] == '<')
		|| (line[*i] == '>' && line[*i + 1] == '>')
		|| line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
		return (1);
	return (0);
}

void	do_the_stuff(t_token **head, t_token **current, int *i, char *line)
{
	if ((line[*i] == '<' && line[*i + 1] == '<')
		|| (line[*i] == '>' && line[*i + 1] == '>')
		|| line[*i] == '<')
		do_the_stuff2(head, current, i, line);
	else if (line[*i] == '>')
	{
		add_token(head, current, ft_strdup(">"), REDIR_OUT);
		*i += 1;
	}
	else if (line[*i] == '|')
	{
		add_token(head, current, ft_strdup("|"), PIPE);
		*i += 1;
	}
}

void	do_the_stuff2(t_token **head, t_token **current, int *i, char *line)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(head, current, ft_strdup("<<"), HERE_DOC);
		*i += 2;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(head, current, ft_strdup(">>"), REDIR_APPEND);
		*i += 2;
	}
	else if (line[*i] == '<')
	{
		add_token(head, current, ft_strdup("<"), REDIR_IN);
		*i += 1;
	}
}

int	process_word(t_tokenizer_state *state)
{
	char	*extracted_value;

	extracted_value = extract_full_argument(state->line, &state->i);
	if (!extracted_value)
		return (0);
	add_token(&state->head, &state->current, extracted_value, WORD);
	return (1);
}

int	process_line(t_tokenizer_state *state)
{
	while (state->line[state->i])
	{
		state->i = skip_space(state->line, state->i);
		if (!state->line[state->i])
			break ;
		if (is_tokenize(&state->i, state->line))
			do_the_stuff(&state->head, &state->current, &state->i, state->line);
		else
		{
			if (!process_word(state))
				return (0);
		}
	}
	return (1);
}
