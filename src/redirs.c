#include "minishell.h"

void	read_until_limiter(int fd, char *limiter)
{
	char	*buf;

	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
		if (ft_strcmp(buf, limiter) == 0)
		{
			free(buf);
			break ;
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
}

void	heredoc_check(t_cmd *cmds)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		exit_free(cmds);
		exit(1);
	}
	read_until_limiter(fd[1], cmds->redirection->file);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
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
