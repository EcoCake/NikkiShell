/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:32:40 by sionow            #+#    #+#             */
/*   Updated: 2025/08/26 22:44:39 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_pipeline *pl)
{
	int	i;

	i = 0;
	if (pl->num_cmds <= 1)
		return ;
	while (i < pl->num_cmds - 1)
	{
		close(pl->pipes[i][0]);
		close(pl->pipes[i][1]);
		free(pl->pipes[i]);
		i++;
	}
	free(pl->pipes);
}

void	init_pipes(t_pipeline *pl, int num_cmds)
{
	int	i;

	i = 0;
	pl->pipes = malloc(sizeof(int *) * (num_cmds - 1));
	if (!pl->pipes)
		exit (1);
	while (i < num_cmds - 1)
	{
		pl->pipes[i] = malloc(sizeof(int) * 2);
		if (!pl->pipes[i] || pipe(pl->pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

void	init_pl(t_pipeline *pl, t_cmd *cmds, t_env_var *env_list)
{
	pl->extcode = 0;
	pl->num_cmds = cmds_count(cmds);
	if (pl->num_cmds > 1)
		init_pipes(pl, pl->num_cmds);
	else
		pl->pipes = NULL;
	pl->num_pids = children_counter(cmds);
	pl->pids = malloc(sizeof(pid_t) * pl->num_pids);
	if (!pl->pids)
	{
		perror("pids");
		exit(1);
	}
	pl->env = env_list;
	pl->head = cmds;
	pl->p_m = 0;
	pl->og_in = dup(0);
	pl->og_out = dup(1);
}
