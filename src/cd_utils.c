/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:16:46 by sionow            #+#    #+#             */
/*   Updated: 2025/08/30 17:26:36 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_error(char *path, t_pipeline *pl, char *to_free)
{
	if (pl->cd_error != 0)
	{
		if (to_free != NULL)
			free(to_free);
		return (1);
	}
	write(2, "nikkishell: cd: ", 16);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	if (to_free != NULL)
		free(to_free);
	pl->extcode = 1;
	pl->cd_error++;
	return (1);
}

char	*fill_path(char *str)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	return (ft_strjoinslash(cwd, &str[2]));
}

int	error_msg_cd(void)
{
	write (2, "cd: ", 4);
	write (2, "OLDPWD not set\n", 16);
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
