/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:07:19 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 18:38:16 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_nodes(t_env_var *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

void	*free_array_on_error(char **array, int size)
{
	while (size > 0)
	{
		size--;
		free(array[size]);
	}
	free(array);
	return (NULL);
}

char	**populate_env_array(char **array, t_env_var *list)
{
	int	i;

	i = 0;
	while (list)
	{
		array[i] = ft_strdup(list->fullstring);
		if (!array[i])
			return (free_array_on_error(array, i));
		i++;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

char	**env_list_array(t_env_var *env_list)
{
	int		count;
	char	**env_array;

	count = count_env_nodes(env_list);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
	{
		perror("malloc fail for env array");
		return (NULL);
	}
	return (populate_env_array(env_array, env_list));
}
