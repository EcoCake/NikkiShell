/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:48:44 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/21 23:54:16 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//create an env_var node from key=value string
t_env_var	*create_env_node(char *env_str)
{
	t_env_var *new;

	new = malloc(sizeof(t_env_var));
	if (!new)
	{
		perror("malloc failed for env node\n");
		return NULL;
	}
	new->next = NULL;
	new->fullstring = ft_strdup(env_str);
	if (!new->fullstring)
	{
		free(new);
		perror("malloc error for env string");
		return NULL;
	}
	return(new);
}

//initialize the environment linked list from the main
t_env_var *init_env_list(char **envp)
{
	t_env_var *head = NULL;
	t_env_var *current = NULL;
	int i;
	i = 0;
	
	while (envp[i])
	{
		t_env_var *new = create_env_node(envp[i]);
		if (!new)
		{
			free_env_list(head);
			return NULL;
		}
		if (!head)
		{
			head = new;
			current = new;
		}
		else
		{
			current->next = new;
			current = new;
		}
		i++;
	}
	return(head);
}
//gets the value of env var based on the key
//returns the pointer to the full string, return null if no key
char	*get_env_value(t_env_var *env_list, const char *key)
{
	char	*equal_sign;
	size_t	key_len;
	
	if (!key || *key == '\0')
		return NULL;
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
	return NULL;
}
//converting linked list into char** array for the execve
//have to free the array and all strings when you call it
//u can use void free_env_array
char **env_list_array(t_env_var *env_list)
{
	int			count;
	t_env_var	*temp;
	char		**env_array;
	count = 0;
	temp = env_list;

	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
	{
		perror("malloc fail for env array\n");
		return NULL;
	}
	temp = env_list;
	count = 0;
	while (temp)
	{
		env_array[count] = ft_strdup(temp->fullstring);
		if (!env_array[count])
		{
			while (count > 0)
			{
				count--;
				free(env_array[count]);
			}
			free(env_array);
			return NULL;
		}
		count++;
		temp = temp->next;
	}
	env_array[count] = NULL;
	return (env_array);
}