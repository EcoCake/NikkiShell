/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:28:09 by sionow            #+#    #+#             */
/*   Updated: 2025/08/26 22:27:33 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	absolute_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	return (1);
}

char	*get_env_path(t_env_var *env)
{
	t_env_var	*f;

	f = env;
	while (f)
	{
		if (ft_strncmp(f->fullstring, "PATH", 4) == 0)
			return (f->fullstring);
		f = f->next;
	}
	return (NULL);
}

char	*env_path(t_cmd *cmds, t_pipeline *pl)
{
	char	**split;
	char	*final_path;
	int		i;

	split = ft_split(get_env_path(pl->env), ':');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		final_path = ft_strjoinslash(split[i], cmds->args[0]);
		if (access(final_path, F_OK | X_OK) == 0)
		{
			free_tab_exec(split);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_tab_exec(split);
	return (NULL);
}
