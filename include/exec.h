#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h> //both for waitpid
# include <sys/wait.h> //^
# include <fcntl.h> // for O_RDONLY
# include <errno.h>

typedef struct s_comms
{
	char 	**caf; //always array of 2, for comm n flag
	char	*red_in;
	char	*red_out;
	char	*hlimiter;
	struct 	s_comms *next;
	int		index;
	int		pipen;
}	t_comms;

#endif