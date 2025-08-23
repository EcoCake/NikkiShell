/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:04:59 by sionow            #+#    #+#             */
/*   Updated: 2025/08/23 18:35:34 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	old_pwd(t_pipeline *pl)
{
	t_env_var	*finger;
	char		*current_pwd;

	finger = pl->env;
	current_pwd = get_env_value(pl->env, "PWD");
	while (finger)
	{
		if (strncmp(finger->fullstring, "OLDPWD=", 7) == 0)
		{
			free(finger->fullstring);
			finger->fullstring = NULL;
			if (current_pwd)
				finger->fullstring = ft_strjoin("OLDPWD=", current_pwd);
			else if (!finger->fullstring)
			{
				perror("ft_strjoin");
				finger->fullstring = ft_strdup("OLDPWD=");
			}
			return ;
		}
		finger = finger->next;
	}
}

void	cd_update(t_pipeline *pl)
{
	t_env_var	*finger;
	char		cwd[PATH_MAX];

	finger = pl->env;
	old_pwd(pl);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return ;
	}
	while (finger)
	{
		if (strncmp(finger->fullstring, "PWD=", 4) == 0)
		{
			free(finger->fullstring);
			finger->fullstring = NULL;
			finger->fullstring = ft_strjoin("PWD=", cwd);
			if (!finger->fullstring)
			{
				perror("ft_strjoin failed in cd_update");
				finger->fullstring = ft_strdup("PWD=");
			}
			return ;
		}
		finger = finger->next;
	}
}

int	cd_tracker(int argc, char **argv, t_pipeline *pl)
{
	if (ft_cd(argc, argv, pl) == 0)
	{
		cd_update(pl);
		return (0);
	}
	else
		return (1);
}
