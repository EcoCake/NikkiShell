#ifndef EXEC_H
# define EXEC_H

# include "parse.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif


typedef struct s_pipeline
{
	char	**env;
	int		**pipes;
	pid_t	*pids;
	int		num_cmds;
}	t_pipeline;

// REDIRECTIONS //

void	heredoc_check(t_pipeline *pl, t_cmd *cmds);
void	read_until_limiter(int fd, char *limiter);
void	redir_in_check(t_pipeline *pl, t_cmd *cmds);
void	redir_out_check(t_pipeline *pl, t_cmd *cmds);
void	redir_append_check(t_pipeline *pl, t_cmd *cmds);
void	close_pipes(t_pipeline *pl);

// BUILTINS //

int	ft_cd(int argc, char **argv);
int	ft_echo(int argc, char **argv);

// UTILS //

char	*get_next_line(int fd);
char	*ft_cpystr(char *s1);
int		ft_strcmp(char *s1, char *s2);
int		ft_strchrnum(char *s, char c);
char	*ft_strjoinslash(char *s1, char *s2);

// FREE //

void	exit_free(t_pipeline *pl, t_cmd *cmds);

#endif
