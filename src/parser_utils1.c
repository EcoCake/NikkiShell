/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:32:20 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/25 17:38:59 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_first_cmd(t_cmd **head, t_cmd **current_cmd, t_token **tokens)
{
	*head = create_cmd_node();
	if (!*head)
		return (0);
	*current_cmd = *head;
	if (!handle_args(*current_cmd, tokens))
		return (0);
	return (1);
}

int	handle_args(t_cmd *current_cmd, t_token **tokens)
{
	current_cmd->args = tokens_to_args_array(tokens);
	if (!current_cmd->args)
		return (0);
	return (1);
}

int	handle_redirections(t_cmd *current_cmd, t_token **tokens)
{
	t_redirection	*new_redir;

	while (*tokens && ((*tokens)->type == REDIR_IN
			|| (*tokens)->type == REDIR_OUT || (*tokens)->type == REDIR_APPEND
			|| (*tokens)->type == HERE_DOC))
	{
		if (!(*tokens)->next || (*tokens)->next->type != WORD)
		{
			printf("syntax error, missing filename after redirect '%s'\n",
				(*tokens)->value);
			return (0);
		}
		new_redir = create_redir_node((*tokens)->type, (*tokens)->next->value);
		if (!new_redir)
			return (0);
		add_redir_to_cmd(current_cmd, new_redir);
		*tokens = (*tokens)->next->next;
	}
	return (1);
}

int	handle_pipe_and_new_cmd(t_cmd **head, t_cmd **current_cmd, t_token **tokens)
{
	if (!(*current_cmd)->args || !(*tokens)->next)
	{
		printf("syntax error '%s'\n", (*tokens)->value);
		return (0);
	}
	*tokens = (*tokens)->next;
	(*current_cmd)->next = create_cmd_node();
	if (!(*current_cmd)->next)
	{
		*head = NULL;
		return (0);
	}
	*current_cmd = (*current_cmd)->next;
	if (!handle_args(*current_cmd, tokens))
		return (0);
	return (1);
}
