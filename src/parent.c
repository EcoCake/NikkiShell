/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:31:38 by sionow            #+#    #+#             */
/*   Updated: 2025/08/26 22:18:38 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if its a builtin that needs a child or parent process
//child == 2 & parent == 0
int	adoption_center(t_cmd *cmds)
{
	if (!cmds->args[0])
		return (1);
	if (((ft_strcmp(cmds->args[0], "echo") == 0)))
		return (2);
	if (((ft_strcmp(cmds->args[0], "pwd") == 0)))
		return (2);
	if (ft_strcmp(cmds->args[0], "env") == 0)
		return (2);
	if (ft_strcmp(cmds->args[0], "cd") == 0)
		return (0);
	if (ft_strcmp(cmds->args[0], "export") == 0)
		return (0);
	if (ft_strcmp(cmds->args[0], "unset") == 0)
		return (0);
	if (ft_strcmp(cmds->args[0], "exit") == 0)
		return (0);
	return (1);
}

void	exec_parent(t_pipeline *pl, t_cmd *cmds, int i)
{
	if (ft_strcmp(cmds->args[0], "exit") != 0)
	{
		pl->og_in = dup(0);
		pl->og_out = dup(1);
	}
	command_redirections(i, pl, cmds, 1);
	pl->extcode = builtin_check(pl, cmds);
	if (pl->extcode != 0 && ft_strcmp(cmds->args[0], "exit") != 0)
	{
		if (adoption_center(cmds) == 1)
			perror(cmds->args[0]);
		free_cmd_list(cmds);
		exit(pl->extcode);
	}
	restore_fds(pl->og_in, pl->og_out, cmds->args[0]);
}

void	child_exec(t_pipeline *pl, t_cmd *cur_cmd, int i)
{
	pl->pids[pl->p_m] = fork();
	if (pl->pids[pl->p_m] == -1)
	{
		perror("fork");
		exit (1);
	}
	else if (pl->pids[pl->p_m] == 0)
	{
		if (cur_cmd->redirection
			&& cur_cmd->redirection->type == HERE_DOC)
			heredoc_check(cur_cmd, pl);
		exec(pl, cur_cmd, i);
	}
	if (cur_cmd->redirection && cur_cmd->redirection->type == HERE_DOC)
		waitpid(pl->pids[pl->p_m], NULL, 0);
	pl->p_m++;
}

//restore after parent process
void	restore_fds(int save_fd_in, int save_fd_out, char *cmds)
{
	if (!cmds || ft_strcmp(cmds, "exit") != 0)
	{
		dup2(save_fd_in, 0);
		dup2(save_fd_out, 1);
		close(save_fd_in);
		close(save_fd_out);
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
