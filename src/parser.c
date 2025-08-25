/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:04:18 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/25 17:37:44 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd_node(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->redirection = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current_cmd;

	if (!tokens)
		return (NULL);
	head = NULL;
	current_cmd = NULL;
	if (!handle_first_cmd(&head, &current_cmd, &tokens))
		return (free_cmd_list(head), NULL);
	while (tokens)
	{
		if (!handle_redirections(current_cmd, &tokens))
			return (free_cmd_list(head), NULL);
		if (!tokens)
			break ;
		if (tokens->type == PIPE)
		{
			if (!handle_pipe_and_new_cmd(&head, &current_cmd, &tokens))
				return (free_cmd_list(head), NULL);
		}
	}
	return (head);
}
