/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:05:48 by sionow            #+#    #+#             */
/*   Updated: 2025/07/25 01:52:08 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h> //for Pathmax
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int	ft_cd_error(char *path, char *to_free)
{
	write(2, "cd: ", 4);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	if (to_free != NULL)
		free(to_free);
	return (1);
}

char	*ft_strjoinslash(char *s1, char *s2)
{
	int		s1m;
	int		s2m;
	int		len;
	char	*finals;

	s1m = 0;
	s2m = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	finals = malloc (sizeof(char) * (len + 2));
	if (!finals)
		return (NULL);
	while (s1[s1m])
	{
		finals[s1m] = s1[s1m];
		s1m++;
	}
	finals[s1m++] = '/';
	while (s2[s2m])
	{
		finals[s1m++] = s2[s2m++];
	}
	finals[s1m] = '\0';
	return (finals);
}

	//line 70 & 77(getcwd(cwd, sizeof(cwd));)fills cwd
int	ft_path_extra(char *str)
{
	char	cwd[PATH_MAX];
	char	*path;

	if (str[0] == '.' && str[1] == '/' && str[2] >= 32 && str[2] <= 126)
	{
		getcwd(cwd, sizeof(cwd));
		path = ft_strjoinslash(cwd, &str[2]);
	}
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
		path = ft_strjoinslash(getenv("HOME"), &str[1]);
	if (getenv("HOME") == NULL)
		return (ft_cd_error("HOME not set\n", path)); //Same as line 129
	if (chdir(path) == -1)
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

int	ft_cd(int argc, char **argv)
{
	char	*path;

	if ((argc == 2) || (argc == 3 && ft_strcmp(argv[2], "~") == 0))
	{
		path = getenv("HOME"); // If he couldnt find the home there is a specific error that returns 1
		if (path == NULL)
			return (ft_cd_error("HOME not set\n", NULL));
	}
	else if (argc == 3)
	{
		if (ft_strcmp(argv[2], ".") == 0)
			path = ".";
		else if (ft_strcmp(argv[2], "..") == 0)
			path = "..";
		else if (ft_strcmp(argv[2], "/") == 0)
			path = "/";
		else if (ft_strcmp(argv[2], "-") == 0)
			path = getenv("OLDPWD"); // Same error as line 129 but replace HOME with OLDPWD (also returns 1)
		else if (ft_paths(argv[2]) == 0 || ft_path_extra(argv[2]) == 0)
			return (0);
	}
	if (chdir(path) == -1)
		return (ft_cd_error(argv[2], NULL));
	return (1);
}

// int main(int argc, char **argv)
// {
//     // Call your ft_cd function with the command-line arguments
//     ft_cd(argc, argv);

//     // Print the current working directory after attempting to change it
//     char cwd[PATH_MAX];
//     if (getcwd(cwd, sizeof(cwd)) != NULL)
//         printf("Current directory: %s\n", cwd);
//     else
//         perror("getcwd() error");
//     return (0);
// }
