#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	free_tab_exec(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	exit_free(t_cmd *cmds)
{
	while (cmds)
	{
		while (cmds->redirection)
		{
			free(cmds->redirection->file);
			cmds->redirection = cmds->redirection->next;
		}
		free_tab_exec(cmds->args);
		cmds = cmds->next;
	}
}

char	**create_args(char *args1, char *args2)
{
	char	**args;

	args = malloc(sizeof(char *) * 3);
	if (!args)
		return (NULL);
	args[0] = ft_strdup(args1);
	args[1] = ft_strdup(args2);
	args[2] = NULL;
	return (args);
}

void	fill_cmds(t_cmd **cmds)
{
	t_cmd	*first;
	t_cmd	*second;

	first = malloc(sizeof(t_cmd));
	first->args = create_args("echo", "hello");
	first->redirection = NULL;
	second = malloc(sizeof(t_cmd));
	second->args = create_args("wc", "-l");
	second->redirection = NULL;
	first->next = second;
	second->next = NULL;
	*cmds = first;
}

int	cmds_count(t_cmd *cmds)
{
	t_cmd	*cpy;
	int		i;

	cpy = cmds;
	i = 0;
	while (cpy)
	{
		i++;
		cpy = cpy->next;
	}
	return (i);
}

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

void	init_pl(t_pipeline *pl, t_cmd *cmds, char **env)
{
	pl->num_cmds = cmds_count(cmds);
	if (pl->num_cmds > 1)
		init_pipes(pl, pl->num_cmds);
	else
		pl->pipes = NULL;
	pl->pids = malloc(sizeof(pid_t) * pl->num_cmds);
	if (!pl->pids)
	{
		perror("pids");
		exit(1);
	}
	pl->env = env;
}

void	command_redirections(int i, t_pipeline *pl, t_cmd *cmds)
{
	if (cmds->redirection)
	{
		if (cmds->redirection->type == HERE_DOC)
			heredoc_check(cmds);
		else if (cmds->redirection->type == REDIR_IN)
			redir_in_check(cmds);
		else if (i > 0 && pl->num_cmds > 1)
			dup2(pl->pipes[i - 1][0], 0);
		if (cmds->redirection->type == REDIR_OUT)
			redir_out_check(cmds);
		else if (cmds->redirection->type == REDIR_APPEND)
			redir_append_check(cmds);
		else if (i < pl->num_cmds - 1 && pl->num_cmds > 1)
			dup2(pl->pipes[i][1], 1);
	}
	else
	{
		if (i > 0 && pl->num_cmds > 1)
			dup2(pl->pipes[i - 1][0], 0);
		if (i < pl->num_cmds - 1 && pl->num_cmds > 1)
			dup2(pl->pipes[i][1], 1);
	}
	close_pipes(pl);
}

int	absolute_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	return (1);
}

char	*env_path(t_cmd *cmds)
{
	char	**split;
	char	*final_path;
	int		i;

	split = ft_split(getenv("PATH"), ':');
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

void	not_builtin(t_pipeline *pl, t_cmd *cmds)
{
	char	*path;

	if (absolute_path(cmds->args[0]) == 0)
		execve(cmds->args[0], cmds->args, pl->env);
	else
	{
		path = env_path(cmds);
		execve(path, cmds->args, pl->env);
	}
	perror("execve");
	exit_free(cmds);
	exit(127);
}

int	get_argc(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds->args[i])
		i++;
	return (i);
}

int	builtin_check(t_pipeline *pl, t_cmd *cmds)
{
	if (ft_strcmp(cmds->args[0], "cd") == 0)
		return (ft_cd(get_argc(cmds), cmds->args));
	if (((ft_strcmp(cmds->args[0], "echo") == 0)))
		return (ft_echo(get_argc(cmds), cmds->args));
	not_builtin(pl, cmds);
	return (127);
}

void	exec(t_pipeline *pl, t_cmd *cmds, int i)
{
	int		error_code;

	command_redirections(i, pl, cmds);
	error_code = builtin_check(pl, cmds);
	if (error_code != 0)
	{
		perror(cmds->args[0]);
		exit_free(cmds);
		exit(error_code);
	}
}

void	command_loop(t_pipeline *pl, t_cmd *cmds)
{
	int	i;
	t_cmd *current_cmd;

	i = 0;
	current_cmd = cmds;
	while (i < pl->num_cmds)
	{
		pl->pids[i] = fork();
		if (pl->pids[i] == -1)
		{
			perror("fork");
			exit (1);
		}
		else if (pl->pids[i] == 0)
		{
			//free(pl->pids);
			exec(pl, current_cmd, i);
		}
		if (i > 0 && pl->num_cmds > 1)
			close(pl->pipes[i - 1][0]);
		if (i < pl->num_cmds - 1 && pl->num_cmds > 1)
			close(pl->pipes[i][1]);
		current_cmd = current_cmd->next;
		i++;
	}
}

// THIS IF FOR MY TEST U CAN COMMENT IT OUT 

int get_arg_count(char **args) {
    int count = 0;
    while (args && args[count])
        count++;
    return count;
}


void exec_main(t_cmd *cmds, t_env_var *env_list, int *last_exit_status_ptr)
{
    t_pipeline  pl;
    int         i;
    int         status;
    char        **exec_envp;

    // Phase 1: Expansion of all arguments and redirections for all commands
    t_cmd *current_cmd_for_expansion = cmds;
    while (current_cmd_for_expansion)
    {
        expand_cmd_args(current_cmd_for_expansion, env_list, *last_exit_status_ptr);
        expand_redirs(current_cmd_for_expansion, env_list, *last_exit_status_ptr);
        current_cmd_for_expansion = current_cmd_for_expansion->next;
    }

    // Phase 2: Handle single built-in commands directly in the parent process
    // This must happen BEFORE pipe setup and forking.
    // We check if it's a single command (no pipes) AND it's a known built-in.
    if (cmds && cmds->args && cmds->args[0] && cmds->next == NULL) // Single command
    {
        // Check for specific built-ins using ft_strncmp
        if (ft_strncmp(cmds->args[0], "echo", 5) == 0)
        {
            *last_exit_status_ptr = ft_echo(get_arg_count(cmds->args), cmds->args);
            // After executing a built-in, no need to proceed with fork/exec/wait.
            return; // Exit exec_main.
        }
        // Add checks for other built-ins here in the same manner:
        // else if (ft_strncmp(cmds->args[0], "cd", 3) == 0) {
        //     *last_exit_status_ptr = builtin_cd(cmds->args, env_list);
        //     return;
        // }
        // else if (ft_strncmp(cmds->args[0], "pwd", 4) == 0) {
        //     *last_exit_status_ptr = builtin_pwd(cmds->args);
        //     return;
        // }
        // ... and so on for export, unset, env, exit.
        // NOTE: 'exit' built-in has special behavior (exiting the shell),
        // so its handling might be slightly different.
    }

    // Phase 3: If not a single built-in, proceed with external command execution or pipelines
    exec_envp = env_list_array(env_list);
    if (!exec_envp) {
        perror("minishell: malloc failed for execve environment array");
        *last_exit_status_ptr = 1; // Set error status for malloc failure
        return; 
    }

    init_pl(&pl, cmds, exec_envp);
    command_loop(&pl, cmds); // This will now primarily handle external commands or piped built-ins

    // Phase 4: Wait for child processes (only for commands that were forked)
    i = 0;
    while (i < pl.num_cmds)
    {
        waitpid(pl.pids[i], &status, 0);
        if (WIFEXITED(status))
            *last_exit_status_ptr = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            *last_exit_status_ptr = 128 + WTERMSIG(status); // For signals like Ctrl+C
        i++;
    }  

    // Phase 5: Cleanup
    close_pipes(&pl);
    free(pl.pids);
    free_env_array(exec_envp);
}




//I COMMENTED FOR TESTING 

// void	exec_main(t_cmd *cmds, char **env)
// {
// 	t_pipeline	pl;
// 	int			i;
// 	int			status;

// 	init_pl(&pl, cmds, env);
// 	command_loop(&pl, cmds);
	
// 	// Wait for all child processes to complete
// 	i = 0;
// 	while (i < pl.num_cmds)
// 	{
// 		waitpid(pl.pids[i], &status, 0);
// 		i++;
// 	}
	
// 	close_pipes(&pl);
// 	free(pl.pids);
// }

// int	main(int argc, char **argv, char **env)
// {
// 	t_cmd	*cmds;

// 	(void)argc;
// 	(void)argv;
// 	cmds = NULL;
// 	fill_cmds(&cmds);
// 	exec_main(cmds, env);
// }
