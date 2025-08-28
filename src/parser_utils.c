/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:38:23 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 17:27:05 by amezoe           ###   ########.fr       */
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
