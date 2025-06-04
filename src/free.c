/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:13:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/06/03 11:01:13 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

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