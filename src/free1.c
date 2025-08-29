/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:57:33 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/29 18:35:01 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*temp;

	while (head)
	{
		temp = head->next;
		if (head->args)
			free_str_array(head->args);
		if (head->redirection)
			free_redir_list(head->redirection);
		free(head);
		head = temp;
	}
}
