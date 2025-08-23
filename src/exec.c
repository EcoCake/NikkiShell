/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:31:54 by sionow            #+#    #+#             */
/*   Updated: 2025/08/23 18:04:49 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	children_counter(t_cmd *cmds)
{
	t_cmd	*finger;
	int		i;

	finger = cmds;
	i = 0;
	while (finger)
	{
		if (adoption_center(finger) != 0)
			i++;
		finger = finger->next;
	}
	return (i);
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
	pl->p_m = 0;
}

void	command_redirections(int i, t_pipeline *pl, t_cmd *cmds, int parent)
{
	if (!cmds->redirection)
	{
		if (i > 0 && pl->num_cmds > 1)
			dup2(pl->pipes[i - 1][0], 0);
		if (i < pl->num_cmds - 1 && pl->num_cmds > 1)
			dup2(pl->pipes[i][1], 1);
	}
	while (cmds->redirection)
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
		cmds->redirection = cmds->redirection->next;
	}
	if (parent == 0)
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
	char	**env_array;

	env_array = env_list_array(pl->env);
	if (absolute_path(cmds->args[0]) == 0)
		execve(cmds->args[0], cmds->args, env_array);
	else
	{
		path = env_path(cmds);
		if (!path)
			path = ft_strdup("");
		execve(path, cmds->args, env_array);
		free(path);
	}
	perror("execve");
	free(pl->pids);
	free_cmd_list(cmds);
	free_env_array(env_array);
	free_env_list(pl->env);
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
		return (cd_tracker(get_argc(cmds), cmds->args, pl));
	if (ft_strcmp(cmds->args[0], "unset") == 0)
		return (ft_unset(get_argc(cmds), cmds->args, pl));
	if (ft_strcmp(cmds->args[0], "export") == 0)
		return (ft_export(get_argc(cmds), cmds->args, pl));
	if (ft_strcmp(cmds->args[0], "exit") == 0)
		return (ft_exit(get_argc(cmds), cmds->args, pl, cmds));
	if (((ft_strcmp(cmds->args[0], "echo") == 0)))
		return (ft_echo(get_argc(cmds), cmds->args));
	if (((ft_strcmp(cmds->args[0], "pwd") == 0)))
		return (ft_pwd(get_argc(cmds), cmds->args, cmds));
	if (((ft_strcmp(cmds->args[0], "env") == 0)))
		return (ft_env(get_argc(cmds), cmds->args, pl));
	not_builtin(pl, cmds);
	return (127);
}

void	exec(t_pipeline *pl, t_cmd *cmds, int i)
{
	int		error_code;

	command_redirections(i, pl, cmds, 0);
	error_code = builtin_check(pl, cmds);
	if (error_code != 0)
	{
		if (adoption_center(cmds) == 1)
			perror(cmds->args[0]);
		free_cmd_list(cmds);
		free(pl->pids);
		exit(error_code);
	}
	else
	{
		free_cmd_list(cmds);
		free(pl->pids);
		free_env_list(pl->env);
		exit(error_code);
	}
}

void	restore_fds(int save_fd_in, int save_fd_out, char *cmds)
{
	if (ft_strcmp(cmds, "exit") != 0)
	{
		dup2(save_fd_in, 0);
		dup2(save_fd_out, 1);
		close(save_fd_in);
		close(save_fd_out);
	}
}

void	exec_parent(t_pipeline *pl, t_cmd *cmds, int i)
{
	int	save_fd_in;
	int	save_fd_out;

	if (ft_strcmp(cmds->args[0], "exit") != 0)
	{
		save_fd_in = dup(0);
		save_fd_out = dup(1);
	}
	command_redirections(i, pl, cmds, 1);
	pl->extcode = builtin_check(pl, cmds);
	if (pl->extcode != 0 && ft_strcmp(cmds->args[0], "exit") != 0)
	{
		perror(cmds->args[0]);
		free_cmd_list(cmds);
		exit(pl->extcode);
	}
	restore_fds(save_fd_in, save_fd_out, cmds->args[0]);
}

void	command_loop(t_pipeline *pl, t_cmd *cmds)
{
	t_cmd	*current_cmd;

	int (i) = 0;
	current_cmd = cmds;
	while (i < pl->num_cmds)
	{
		if (adoption_center(current_cmd) != 0)
		{
			pl->pids[pl->p_m] = fork();
			if (pl->pids[pl->p_m] == -1)
			{
				perror("fork");
				exit (1);
			}
			else if (pl->pids[pl->p_m] == 0)
				exec(pl, current_cmd, i);
			pl->p_m++;
		}
		else
			exec_parent(pl, current_cmd, i);
		if (i > 0 && pl->num_cmds > 1)
			close(pl->pipes[i - 1][0]);
		if (i < pl->num_cmds - 1 && pl->num_cmds > 1)
			close(pl->pipes[i][1]);
		current_cmd = current_cmd->next;
		i++;
	}
}

// THIS IF FOR MY TEST U CAN COMMENT IT OUT 
/*
int get_arg_count(char **args) {
    int	count = 0;
    while (args && args[count])
        count++;
    return (count);
}*/

int	exec_main(t_cmd *cmds, t_env_var *env_list)
{
	t_pipeline	pl;
	int			i;
	int			status;

	i = 0;
	init_pl(&pl, cmds, env_list);
	command_loop(&pl, cmds);
	while (i < pl.num_pids)
	{
		waitpid(pl.pids[i], &status, 0);
		i++;
	}
	close_pipes(&pl);
	free(pl.pids);
	return (pl.extcode);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_cmd	*cmds;

// 	(void)argc;
// 	(void)argv;
// 	cmds = NULL;
// 	fill_cmds(&cmds);
// 	exec_main(cmds, env);
// }
