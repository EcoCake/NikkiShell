/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:05:48 by sionow            #+#    #+#             */
/*   Updated: 2025/08/26 17:18:08 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_path_extra(char *str, t_pipeline *pl)
{
	char	cwd[PATH_MAX];
	char	*path;

	path = NULL;
	if (str[0] == '.' && str[1] == '/' && str[2] >= 32 && str[2] <= 126)
		path = fill_path(str);
	else if (str[0] == '.' && str[1] == '.' && str[2] == '/'
		&& (str[3] >= 32 && str[3] <= 126))
	{
		getcwd(cwd, sizeof(cwd));
		path = ft_strjoinslash(cwd, str);
		if (chdir("..") == -1)
			return (ft_cd_error(str, NULL));
	}
	else if ((str[0] == '~') && (str[1] == '/')
		&& (str[2] >= 32 && str[2] <= 126))
		path = ft_strjoinslash(get_env_value(pl->env, "HOME"), &str[1]);
	if (get_env_value(pl->env, "HOME") == NULL)
		return (ft_cd_error("HOME not set\n", path));
	if (path && chdir(path) == -1)
		return (ft_cd_error(str, path));
	free(path);
	return (0);
}

int	ft_paths(char *str)
{
	if ((str[0] == '/')
		&& ((str[1] >= 32 && str[1] <= 46) || (str[1] >= 48 && str[1] <= 126)))
	{
		if (chdir(str) == -1)
			return (ft_cd_error(str, NULL));
		return (0);
	}
	else if (str[0] >= 33 && str[0] <= 125 && str[0] != '.')
	{
		if (chdir(str) == -1)
			return (ft_cd_error(str, NULL));
		return (0);
	}
	return (1);
}

void	linesavercd(t_pipeline *pl, char *path)
{
	path = get_env_value(pl->env, "OLDPWD");
	if (path == NULL)
		error_msg_cd();
}

int	ft_cd(int argc, char **argv, t_pipeline *pl)
{
	char	*path;

	path = NULL;
	if ((argc == 1) || (argc == 2 && ft_strcmp(argv[1], "~") == 0))
	{
		path = get_env_value(pl->env, "HOME");
		if (path == NULL)
			return (ft_cd_error("HOME not set\n", NULL));
	}
	else if (argc == 2)
	{
		if (ft_strcmp(argv[1], ".") == 0)
			path = ".";
		else if (ft_strcmp(argv[1], "..") == 0)
			path = "..";
		else if (ft_strcmp(argv[1], "/") == 0)
			path = "/";
		else if (ft_strcmp(argv[1], "-") == 0)
			linesavercd(pl, path);
		else if (ft_paths(argv[1]) == 0 || ft_path_extra(argv[1], pl) == 0)
			return (0);
	}
	if (!path || chdir(path) == -1)
		return (ft_cd_error(argv[1], NULL));
	return (0);
}
