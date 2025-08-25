/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:38:23 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/25 17:57:00 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*create_redir_node(t_token_types type, char *file)
{
	t_redirection	*new_redir;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free (new_redir);
		return (NULL);
	}
	new_redir->next = NULL;
	return (new_redir);
}

int	add_redir_to_cmd(t_cmd *cmd, t_redirection *new_redir)
{
	t_redirection	*current;

	if (!cmd || !new_redir)
		return (-1);
	if (!cmd->redirection)
		cmd->redirection = new_redir;
	else
	{
		current = cmd->redirection;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	return (0);
}

int	count_word_tokens(t_token *head)
{
	int	count;

	count = 0;
	while (head && head->type == WORD)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**tokens_to_args_array(t_token **current_token)
{
	int	count;

	count = count_word_tokens(*current_token);
	return (copy_word_tokens(current_token, count));
}
