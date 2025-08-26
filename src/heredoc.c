/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:11:02 by sionow            #+#    #+#             */
/*   Updated: 2025/08/26 21:58:17 by sionow           ###   ########.fr       */
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
			printf("nikkishell: warning: here-document at line 1 delimited by "
				"end-of-file (wanted `%s')\n", limiter);
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

void	heredoc_exit(t_cmd *cmds, t_pipeline *pl, int fd)
{
	close(fd);
	close(pl->og_in);
	close(pl->og_out);
	free_env_list(pl->env);
	free_cmd_list(cmds);
	free(pl->pids);
	close_pipes(pl);
}

//l74 signal goes back to alicia's way so act the same way as before heredoc
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
		heredoc_exit(cmds, pl, fd[0]);
		exit(130);
	}
	dup2(fd[0], 0);
	close(fd[0]);
	g_last_signal = 0;
	signal(SIGINT, handle_sigint_rl);
}
