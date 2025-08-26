/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 23:59:53 by sionow            #+#    #+#             */
/*   Updated: 2025/08/26 16:49:33 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset_head(char *str, t_pipeline *pl)
{
	t_env_var	*finger;
	t_env_var	*temp;

	finger = pl->env;
	temp = finger;
	if ((finger && ft_strncmp(str, finger->fullstring, ft_strlen(str)) == 0)
		&& finger->fullstring[ft_strlen(str)] == '=' )
	{
		temp = pl->env;
		pl->env = pl->env->next;
		free(temp->fullstring);
		free(temp);
		return (0);
	}
	return (1);
}

void	unset_last(char *str, t_pipeline *pl)
{
		t_env_var	*finger;
	t_env_var	*temp;

	finger = pl->env;
	temp = finger;
	while (finger->next && finger->next->next)
		finger = finger->next;
	if (finger->next && finger->next->next == NULL 
		&& ft_strncmp(str, finger->next->fullstring, ft_strlen(str)) == 0
		&& finger->next->fullstring[ft_strlen(str)] == '=')
	{
		temp = finger->next;
		finger->next = NULL;
		free(temp->fullstring);
		free(temp);
	}
}

void	unset_env(char *str, t_pipeline *pl)
{
	t_env_var	*f;
	t_env_var	*temp;

	if (unset_head(str, pl) == 0)
		return ;
	f = pl->env;
	temp = f;
	while (f && f->next
		&& ft_strncmp(str, f->fullstring, ft_strlen(str)) != 0)
	{
		if (f && f->next
			&& ft_strncmp(str, f->next->fullstring, ft_strlen(str)) == 0
			&& f->next->fullstring[ft_strlen(str)] == '=')
		{
			temp = f->next;
			f->next = temp->next;
			free(temp->fullstring);
			free(temp);
			return ;
		}
		f = f->next;
	}
	unset_last(str, pl);
	return ;
}

int ft_unset(int argc, char **argv, t_pipeline *pl)
{
	int	i;

	i = 1;
	if (argc == 1)
		return (0);
	if (argc > 1)
	{
		while (i < argc)
		{
			unset_env(argv[i], pl);
			i++;
		}
	}
	return (0);
}
