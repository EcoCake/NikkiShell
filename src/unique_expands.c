/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_expands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 00:21:31 by sionow            #+#    #+#             */
/*   Updated: 2025/08/31 00:38:57 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_empty(t_pipeline *pl, int parent)
{
	if (parent == 1)
	{
		pl->extcode = 0;
		return (1);
	}
	free_env_list(pl->env);
	free_cmd_list(pl->head);
	free(pl->pids);
	exit(0);
}

int	expand_pwd(t_pipeline *pl, int parent, char *str)
{
	pl->extcode = 126;
	ft_putstr_fd("nikkishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	if (parent == 0)
	{
		free_env_list(pl->env);
		free_cmd_list(pl->head);
		free(pl->pids);
		exit(126);
	}
	return (1);
}

int	check_expand(char *str, t_pipeline *pl, int parent)
{
	t_env_var	*f;
	char		*i;

	f = pl->env;
	if (str && !str[0])
		return (expand_empty(pl, parent));
	while (f)
	{
		if (ft_strncmp(f->fullstring, "PWD=", 4) != 0)
		{
			f = f->next;
			continue ;
		}
		i = ft_strchr(f->fullstring, '=');
		i++;
		if (ft_strcmp(i, str) == 0)
			return (expand_pwd(pl, parent, str));
		f = f->next;
	}
	return (0);
}
