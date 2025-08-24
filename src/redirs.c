/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:02:59 by sionow            #+#    #+#             */
/*   Updated: 2025/08/24 20:49:30 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_until_limiter(int fd, char *limiter)
{
	char	*buf;

	signal(SIGINT, signalhandler);
	while (g_last_signal == 0)
	{
		buf = readline("> ");
		if (!buf)
		{
			printf("nikkishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		if (ft_strcmp(buf, limiter) == 0)
		{
			free(buf);
			break ;
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	return (g_last_signal);
}

// NEED TO DO HEREDOC BEFORE THE FUNCTION ELSE HEREDOC TOO SLOW TO TRANSFER TO PIPE

void	heredoc_check(t_cmd *cmds, t_pipeline *pl)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		exit_free(cmds);
		exit(1);
	}
	g_last_signal = 0;
	pl->extcode = read_until_limiter(fd[1], cmds->redirection->file);
	close(fd[1]);
	if (g_last_signal == SIGINT)
	{
		g_last_signal = 0;
		close(fd[0]);
		close(pl->og_in);
		close(pl->og_out);
		free_env_list(pl->env);
		free_cmd_list(cmds);
		free(pl->pids);
		close_pipes(pl);
		exit(130);
	}
	dup2(fd[0], 0);
	close(fd[0]);
	g_last_signal = 0;
	signal(SIGINT, handle_sigint_rl); //goes back to alicia's way so act the same way as before heredoc
}

void	redir_in_check(t_cmd *cmds)
{
	int	fd;

	fd = open(cmds->redirection->file, O_RDONLY);
	if (fd == -1)
	{
		perror(cmds->redirection->file);
		exit_free(cmds);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

void	redir_out_check(t_cmd *cmds)
{
	int	fd;

	fd = open(cmds->redirection->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror(cmds->redirection->file);
		exit_free(cmds);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	redir_append_check(t_cmd *cmds)
{
	int	fd;

	fd = open(cmds->redirection->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror(cmds->redirection->file);
		exit_free(cmds);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}
