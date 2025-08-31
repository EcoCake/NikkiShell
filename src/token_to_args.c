/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:27:19 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/31 00:12:54 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args_on_error(char **args_array, int size)
{
	while (size > 0)
	{
		size--;
		free(args_array[size]);
	}
	free(args_array);
}

int	skip_redir_tokens(t_token **current)
{
	t_token_types	type;

	while (*current)
	{
		type = (*current)->type;
		if (type == REDIR_APPEND || type == REDIR_IN
			|| type == REDIR_OUT || type == HERE_DOC)
		{
			if ((*current)->next)
				*current = (*current)->next->next;
			else
			{
				*current = NULL;
				return (1);
			}
		}
		else
			break ;
	}
	return (0);
}

int	populate_args_array(char **args, t_token **current, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if ((*current)->type == PIPE)
			break ;
		skip_redir_tokens(current);
		if (!*current)
			break ;
		args[i] = ft_strdup((*current)->value);
		if (!args[i])
		{
			perror("malloc fail for arg str");
			return (0);
		}
		*current = (*current)->next;
		i++;
	}
	return (1);
}

char	**tokens_to_args_array(t_token **current_token)
{
	char	**args_array;
	int		count;

	count = count_word_tokens(*current_token);
	args_array = malloc(sizeof(char *) * (count + 1));
	if (!args_array)
	{
		perror("malloc fail for args array");
		return (NULL);
	}
	if (!populate_args_array(args_array, current_token, count))
	{
		free_args_on_error(args_array, count);
		return (NULL);
	}
	args_array[count] = NULL;
	return (args_array);
}
