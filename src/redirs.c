/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:02:59 by sionow            #+#    #+#             */
/*   Updated: 2025/08/26 21:11:01 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in_check(t_cmd *cmds, t_redirection *f)
{
	int	fd;

	fd = open(f->file, O_RDONLY);
	if (fd == -1)
	{
		perror(f->file);
		ft_putstr_fd("gasdgf\n\n", 2);
		exit_free(cmds);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

void	redir_out_check(t_cmd *cmds, t_redirection *f)
{
	int	fd;

	fd = open(f->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror(f->file);
		exit_free(cmds);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	redir_append_check(t_cmd *cmds, t_redirection *f)
{
	int	fd;

	fd = open(f->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror(f->file);
		exit_free(cmds);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}
