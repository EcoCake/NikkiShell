/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:04:18 by amezoe            #+#    #+#             */
/*   Updated: 2025/07/25 01:50:35 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *create_cmd_node()
{
	t_cmd *new;
	
	new = malloc(sizeof(t_cmd));
	if (!new)
		return NULL;
	new->args = NULL;
	new->redirection = NULL;
	new->next = NULL;
	return (new);
}


//i will have to split this up i know
//i need to start examprepping so forgive me for 
//spaghetti code

t_cmd *parse_tokens(t_token *tokens)
{
	t_cmd *head = NULL;
	t_cmd *current_cmd = NULL;
	t_token *current_token = tokens;
	t_redirection *new_redir;

	if (!tokens)
		return NULL;
	while (current_token)
	{
		if(!head || current_token->type == PIPE)
		{
			if (current_token->type == PIPE)
			{
				if (!current_cmd || !current_token->next)
				{
					printf("syntax error '%s'\n", current_token->value);
					free_cmd_list(head);
					return (NULL);
				}
				current_token = current_token->next; // skip pipe t
			}
			if (!head)
			{
				head = create_cmd_node();
				current_cmd = head;
			}
			else
			{
				current_cmd->next = create_cmd_node();
				current_cmd = current_cmd->next;	
			}
			if(!current_cmd)
			{
				free(head);
				return (NULL);
			}
		}
		current_cmd->args = tokens_to_args_array(&current_token);
		if (!current_cmd->args)
		{
			free_cmd_list(head);
			return NULL;
		}
		//redirections after cmd/args before next pipe
		while (current_token && (current_token->type == REDIR_IN ||
			current_token->type == REDIR_OUT || 
			current_token->type == REDIR_APPEND || 
			current_token->type == HERE_DOC))
			{
				//check if redir without filename
				if(!current_token->next || current_token->next->type != WORD)
				{
					printf("syntax error, missing filename after redit '%s'\n", current_token->value);
					free_cmd_list(head);
					return (NULL);
				}
				new_redir = create_redir_node(current_token->type, current_token->next->value);
				if (!new_redir)
				{
					free_cmd_list(head);
					return (NULL);
				}
				add_redir_to_cmd(current_cmd, new_redir);
				current_token = current_token->next->next;
			}
	}
	return(head);
}