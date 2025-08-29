/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:38:15 by sionow            #+#    #+#             */
/*   Updated: 2025/08/30 00:43:51 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchre(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strdupexp(const char *s)
{
	char	*dup;
	int		i;
	int		j;
	int		equal;

	dup = malloc(ft_strlen(s) + 3);
	i = 0;
	j = 0;
	equal = 0;
	while (s[i])
	{
		dup[j] = s[i];
		if (equal == 0 && s[i] == '=')
		{
			equal = 1;
			j++;
			dup[j] = '"';
		}
		j++;
		i++;
	}
	dup[j] = '"';
	dup[j + 1] = '\0';
	return (dup);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

int	ft_strchrn(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	add_env_var(char *var, t_pipeline *pl)
{
	t_env_var	*new;
	t_env_var	*curr;

	new = create_env_node(var);
	if (!new)
		return ;
	curr = pl->env;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}
