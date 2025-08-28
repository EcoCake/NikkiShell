/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:04:18 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 17:16:35 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmd_new_node(t_cmd **head, t_cmd **current_cmd)
{
	*head = create_cmd_node();
	*current_cmd = *head;
}

int	check_pipe(t_token **current_token, t_cmd **current_cmd, t_cmd **head)
{
	if ((*current_token)->type == PIPE)
	{
		if (!(*current_cmd) || !(*current_token)->next)
		{
			printf("syntax error '%s'\n", (*current_token)->value);
			free_cmd_list(*head);
			return (0);
		}
		*current_token = (*current_token)->next;
	}
	if (!(*head))
		create_cmd_new_node(head, current_cmd);
	else
	{
		(*current_cmd)->next = create_cmd_node();
		*current_cmd = (*current_cmd)->next;
	}
	if (!*current_cmd)
	{
		free(*head);
		return (0);
	}
	return (1);
}

int	is_redir_heredoc(t_token *current_token)
{
	if (current_token && (current_token->type == REDIR_IN
			|| current_token->type == REDIR_OUT
			|| current_token->type == REDIR_APPEND
			|| current_token->type == HERE_DOC))
		return (1);
	return (0);
}

int	is_norm(t_cmd **cur_c, t_token **cur_t, t_cmd **head, t_redirection **n_red)
{
	if (!(*cur_c)->args)
	{
		free_cmd_list(*head);
		return (0);
	}
	while (is_redir_heredoc(*cur_t))
	{
		if (!(*cur_t)->next || (*cur_t)->next->type != WORD)
		{
			printf("syntax error, missing filename after redir '%s'\n",
				(*cur_t)->value);
			free_cmd_list(*head);
			return (0);
		}
		*n_red = create_redir_node((*cur_t)->type, (*cur_t)->next->value);
		if (!*n_red)
		{
			free_cmd_list(*head);
			return (0);
		}
		add_redir_to_cmd(*cur_c, *n_red);
		*cur_t = (*cur_t)->next->next;
	}
	return (1);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd			*head;
	t_cmd			*current_cmd;
	t_token			*current_token;
	t_redirection	*new_redir;

	head = NULL;
	current_cmd = NULL;
	current_token = tokens;
	if (!tokens)
		return (NULL);
	while (current_token)
	{
		if (!head || current_token->type == PIPE)
			if (!check_pipe(&current_token, &current_cmd, &head))
				return (NULL);
		current_cmd->args = tokens_to_args_array(&current_token);
		if (!is_norm(&current_cmd, &current_token, &head, &new_redir))
			return (NULL);
	}
	return (head);
}
