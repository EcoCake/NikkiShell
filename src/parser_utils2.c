/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:54:27 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/25 18:02:59 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_and_free(char **args, int size)
{
	while (size > 0)
	{
		size--;
		free(args[size]);
	}
	free(args);
	perror("malloc fail for arg str");
	return (NULL);
}

int	dup_args_loop(t_token **token, char **args_array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		args_array[i] = ft_strdup((*token)->value);
		if (!args_array[i])
			return (0);
		(*token) = (*token)->next;
		i++;
	}
	args_array[i] = NULL;
	return (1);
}

char	**copy_word_tokens(t_token **token, int count)
{
	char	**args_array;

	args_array = ft_calloc(count + 1, sizeof(char *));
	if (!args_array)
	{
		perror("malloc fail for args array");
		return (NULL);
	}
	if (!dup_args_loop(token, args_array, count))
		return (copy_and_free(args_array, count));
	return (args_array);
}

int	count_word_tokens1(t_token *head)
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
