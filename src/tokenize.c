/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:00 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/26 21:36:01 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char* extract_full_argument(const char* line, int* position)
{
    int start = *position;
    int in_squote = 0;
    int in_dquote = 0;

    while (line[*position])
    {
        char current_char = line[*position];

        if (current_char == '\'' && !in_dquote)
            in_squote = !in_squote;
        else if (current_char == '"' && !in_squote)
            in_dquote = !in_dquote;
        if ((is_space(current_char) || is_operator(current_char)) && !in_squote && !in_dquote)
            break;
        (*position)++;
    }
    if (in_squote || in_dquote)
    {
        fprintf(stderr, "syntax error: unclosed quote\n");
        return NULL;
    }
    return ft_substr(line, start, *position - start);
}


t_token *tokenize(char *line)
{
	t_token	*head;
	t_token	*current;
	int		i;
	char	*extracted_value;

	head = NULL;
	current = NULL;
	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		i = skip_space(line, i);
		if (!line[i])
			break ;
		if (line[i] == '<' && line[i + 1] == '<')
		{
			add_token(&head, &current, ft_strdup("<<"), HERE_DOC);
			i += 2;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			add_token(&head, &current, ft_strdup(">>"), REDIR_APPEND);
			i += 2;
		}
		else if (line[i] == '<')
		{
			add_token(&head, &current, ft_strdup("<"), REDIR_IN);
			i += 1;
		}
		else if (line[i] == '>')
		{
			add_token(&head, &current, ft_strdup(">"), REDIR_OUT);
			i += 1;
		}
		else if (line[i] == '|')
		{
			add_token(&head, &current, ft_strdup("|"), PIPE);
			i += 1;
		}
		else
		{
			extracted_value = extract_full_argument(line, &i);
			if (!extracted_value)
			{
				free_token_list(head);
				return (NULL);
			}
			add_token(&head, &current, extracted_value, WORD);
		}
	}
	return (head);
}
