/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:28:09 by sionow            #+#    #+#             */
/*   Updated: 2025/08/31 19:04:17 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	uncheck(char *str)
{
	if (str[0] != '.' && str[0] != '/')
		return (1);
	if (ft_strncmp("/bin", str, 4) == 0)
		return (1);
	if (ft_strncmp("/usr", str, 4) == 0)
		return (1);
	if (ft_strncmp("/snap", str, 5) == 0)
		return (1);
	return (0);
}

void	check_direc(char *str, t_pipeline *pl)
{
	int	fd;

	if (uncheck(str))
		return ;
	fd = open(str, O_RDONLY);
	close_pipes(pl);
	free(pl->pids);
	free_env_list(pl->env);
	if (fd < 0)
	{
		ft_putstr_fd("nikkishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_cmd_list(pl->head);
		exit(127);
	}
	ft_putstr_fd("nikkishell: ", 2);
	ft_putstr_fd(str, 2);
	if (chdir(str) != -1)
		ft_putstr_fd(": Is a directory\n", 2);
	else
		ft_putstr_fd(": Permission denied\n", 2);
	close(fd);
	free_cmd_list(pl->head);
	exit(126);
}

int	absolute_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	return (1);
}

char	*get_env_path(t_env_var *env)
{
	t_env_var	*f;

	f = env;
	while (f)
	{
		if (ft_strncmp(f->fullstring, "PATH", 4) == 0)
			return (f->fullstring);
		f = f->next;
	}
	return (NULL);
}

char	*env_path(t_cmd *cmds, t_pipeline *pl)
{
	char	**split;
	char	*final_path;
	int		i;

	split = ft_split(get_env_path(pl->env), ':');
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
