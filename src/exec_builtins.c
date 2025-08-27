/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:37:49 by sionow            #+#    #+#             */
/*   Updated: 2025/08/27 16:21:49 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join3(char *s1, char *s2, char *s3)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(s1, s2);
	res = ft_strjoin(temp, s3);
	free(temp);
	return (res);
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
		path = env_path(cmds, pl);
		if (!path)
			path = ft_strdup("");
		execve(path, cmds->args, env_array);
		free(path);
	}
	path = join3("nikkishell: ", cmds->args[0], ": command not found\n");
	ft_putstr_fd(path, 2);
	free(path);
	free(pl->pids);
	free_cmd_list(pl->head);
	free_env_array(env_array);
	free_env_list(pl->env);
	exit(127);
}

int	builtin_check(t_pipeline *pl, t_cmd *cmds)
{
	if (!cmds->args[0])
		return (127);
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
		return (ft_pwd(get_argc(cmds), cmds->args, pl));
	if (((ft_strcmp(cmds->args[0], "env") == 0)))
		return (ft_env(get_argc(cmds), cmds->args, pl));
	not_builtin(pl, cmds);
	return (127);
}
