/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:31:54 by sionow            #+#    #+#             */
/*   Updated: 2025/08/31 00:06:36 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_loop(t_cmd *cmds, t_pipeline *pl, int i)
{
	t_redirection	*finger;

	finger = cmds->redirection;
	while (finger)
	{
		if (finger->type == HERE_DOC)
		{
			if (i < pl->num_cmds - 1 && pl->num_cmds > 1)
				dup2(pl->pipes[i][1], 1);
		}
		else if (finger->type == REDIR_IN)
			redir_in_check(pl, finger);
		else if (i > 0 && pl->num_cmds > 1)
			dup2(pl->pipes[i - 1][0], 0);
		if (finger->type == REDIR_OUT)
			redir_out_check(pl, finger);
		else if (finger->type == REDIR_APPEND)
			redir_append_check(pl, finger);
		else if (i < pl->num_cmds - 1 && pl->num_cmds > 1)
			dup2(pl->pipes[i][1], 1);
		finger = finger->next;
	}
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
	redir_loop(cmds, pl, i);
	if (parent == 0)
		close_pipes(pl);
}

void	exec(t_pipeline *pl, t_cmd *cmds, int i)
{
	int		error_code;

	close(pl->og_in);
	close(pl->og_out);
	command_redirections(i, pl, cmds, 0);
	error_code = builtin_check(pl, cmds);
	if (error_code != 0)
	{
		if (cmds->args[0] && adoption_center(cmds) == 1)
			perror(cmds->args[0]);
		free_cmd_list(pl->head);
		free_env_list(pl->env);
		free(pl->pids);
		exit(error_code);
	}
	else
	{
		free_cmd_list(pl->head);
		free(pl->pids);
		free_env_list(pl->env);
		exit(error_code);
	}
}

void	command_loop(t_pipeline *pl, t_cmd *cmds)
{
	t_cmd	*current_cmd;

	int (i) = 0;
	current_cmd = cmds;
	while (i < pl->num_cmds)
	{
		if (adoption_center(current_cmd) != 0)
			child_exec(pl, current_cmd, i);
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

int	exec_main(t_cmd *cmds, t_env_var *env_list, int last_exit_status)
{
	t_pipeline	pl;
	int			i;
	int			status;

	i = 0;
	init_pl(&pl, cmds, env_list);
	pl.extcode = last_exit_status;
	command_loop(&pl, cmds);
	while (i < pl.num_pids)
	{
		waitpid(pl.pids[i], &status, 0);
		pl.extcode = WEXITSTATUS(status);
		i++;
	}
	close_pipes(&pl);
	free(pl.pids);
	restore_fds(pl.og_in, pl.og_out, NULL, NULL);
	return (pl.extcode);
}
