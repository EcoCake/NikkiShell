/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:13:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/07/24 13:49:08 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_env_list(t_env_var *head)
{
	t_env_var	*temp;
	while (head)
	{
		temp = head->next;
		free(head->fullstring);
		free(head);
		head = temp;
	}
}

void	free_env_array(char **env_array)
{
	int i;
	i = 0;
	if (env_array[i])
	{
		while (env_array[i])
		{
			free(env_array[i]);
			i++;
		}
		free(env_array);
	}
}

void free_str_array(char **array)
{
	int i;
	i = 0;
	
	if (!array)
		return;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void free_redir_list(t_redirection *head)
{
	t_redirection *temp;
	while (head)
	{
		temp = head->next;
		free(head->file);
		free(head);
		head = temp;
	}
}

void free_cmd_list(t_cmd *head)
{
	t_cmd *temp;
	while (head)
	{
		temp = head->next;
		if (head->args)
			free_str_array(head->args); //free the char** args array
		if (head->redirection)
			free_redir_list(head->redirection);
		free(head);
		head = temp;
	}
}