/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:12:30 by sionow            #+#    #+#             */
/*   Updated: 2025/08/30 17:33:57 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env_exit(t_pipeline *pl)
{
	free(pl->pids);
	close_pipes(pl);
	free_env_list(pl->env);
	free_cmd_list(pl->head);
}

int	ft_env(int argc, char **argv, t_pipeline *pl)
{
	t_env_var	*finger;

	finger = pl->env;
	if (argc == 1)
	{
		while (finger)
		{
			if (ft_strchre(finger->fullstring, '=') == 0)
			{
				write(1, finger->fullstring, ft_strlen(finger->fullstring));
				write(1, "\n", 1);
			}
			finger = finger->next;
		}
	}
	else
	{
		write(2, "env: '", 6);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "': No such file or directory\n", 29);
		clean_env_exit(pl);
		exit(127);
	}
	return (0);
}
