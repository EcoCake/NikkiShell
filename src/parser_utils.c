/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:38:23 by amezoe            #+#    #+#             */
/*   Updated: 2025/06/12 09:57:44 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

t_redirection	*create_redir_node(t_token_types type, char *file)
{
	t_redirection *new_redir;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return NULL;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free (new_redir);
		return NULL;
	}
	new_redir->next = NULL;
	return(new_redir);
}

int	add_redir_to_cmd(t_cmd *cmd, t_redirection *new_redir)
{
	t_redirection	*current;

	if (!cmd || !new_redir)
		return (-1);
	if (!cmd->redirerction)
		cmd->redirerction = new_redir;
	else
		{
			current = cmd->redirerction;
			while (current->next)
				current = current->next;
			current->next = new_redir;
		}
		return 0;
}

int count_word_tokens(t_token *head)
{
	int count;
	count = 0;
	while (head && head->type == WORD)
	{
		count++;
		head = head->next;
	}
	return (count);
}

//converting WORD tokens into nulltermed char** array
//processes only the consecutive word tokens from current_token and will go to next after its processed

char	**tokens_to_args_array(t_token **current_token)
{
	char	**args_array;
	t_token	*temp;
	int		count;
	int		i;
	temp = *current_token;
	count = 0;
	i = 0;

	while (temp && temp->type == WORD)
	{
		count++;
		temp = temp->next;
	}
	args_array = malloc(sizeof(char *) * (count + 1));
	if (!args_array)
		return NULL;
	while (*current_token && (*current_token)->type == WORD)
	{
		args_array[i] = ft_strdup((*current_token)->value);
		if (!args_array[i])
		{
			while (i > 0)
			{
				i--;
				free(args_array[i]);
			}
			free(args_array);
			perror("malloc fail for arg str");
			return NULL;
		}
		(*current_token) = (*current_token)->next;
		i++;
	}
	args_array[i] = NULL;
	return (args_array);
}
