/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:25:08 by sionow            #+#    #+#             */
/*   Updated: 2025/08/26 21:27:46 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_argc(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds->args[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	free_tab_exec(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	exit_free(t_cmd *cmds)
{
	while (cmds)
	{
		while (cmds->redirection)
		{
			free(cmds->redirection->file);
			cmds->redirection = cmds->redirection->next;
		}
		free_tab_exec(cmds->args);
		cmds = cmds->next;
	}
}

int	cmds_count(t_cmd *cmds)
{
	t_cmd	*cpy;
	int		i;

	cpy = cmds;
	i = 0;
	while (cpy)
	{
		i++;
		cpy = cpy->next;
	}
	return (i);
}
