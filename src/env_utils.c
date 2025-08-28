/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:48:44 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 18:10:02 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*create_env_node(char *env_str)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	if (!new)
	{
		perror("malloc failed for env node\n");
		return (NULL);
	}
	new->next = NULL;
	new->fullstring = ft_strdup(env_str);
	if (!new->fullstring)
	{
		free(new);
		perror("malloc error for env string");
		return (NULL);
	}
	return (new);
}

void	append_env_node(t_env_var **head, t_env_var **current, t_env_var *new)
{
	if (*head == NULL)
	{
		*head = new;
		*current = new;
	}
	else
	{
		(*current)->next = new;
		*current = new;
	}
}

t_env_var	*init_env_list(char **envp)
{
	t_env_var	*head;
	t_env_var	*current;
	t_env_var	*new;
	int			i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new = create_env_node(envp[i]);
		if (!new)
		{
			free_env_list(head);
			return (NULL);
		}
		append_env_node(&head, &current, new);
		i++;
	}
	return (head);
}

char	*get_env_value(t_env_var *env_list, const char *key)
{
	char	*equal_sign;
	size_t	key_len;

	if (!key || *key == '\0')
		return (NULL);
	key_len = ft_strlen(key);
	while (env_list)
	{
		equal_sign = ft_strchr(env_list->fullstring, '=');
		if (equal_sign && (ft_strncmp(env_list->fullstring, key, key_len) == 0)
			&& (env_list->fullstring[key_len] == '='))
		{
			return (equal_sign + 1);
		}
		env_list = env_list->next;
	}
	return (NULL);
}
