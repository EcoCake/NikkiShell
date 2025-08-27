/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:02:59 by sionow            #+#    #+#             */
/*   Updated: 2025/08/27 15:31:40 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in_check(t_pipeline *pl, t_redirection *f)
{
	int	fd;

	fd = open(f->file, O_RDONLY);
	if (fd == -1)
	{
		perror(f->file);
		close_pipes(pl);
		free(pl->pids);
		free_cmd_list(pl->head);
		free_env_list(pl->env);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

void	redir_out_check(t_pipeline *pl, t_redirection *f)
{
	int	fd;

	fd = open(f->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror(f->file);
		close_pipes(pl);
		free(pl->pids);
		free_cmd_list(pl->head);
		free_env_list(pl->env);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	redir_append_check(t_pipeline *pl, t_redirection *f)
{
	int	fd;

	fd = open(f->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror(f->file);
		close_pipes(pl);
		free(pl->pids);
		free_cmd_list(pl->head);
		free_env_list(pl->env);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}
