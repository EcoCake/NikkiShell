/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:04:59 by sionow            #+#    #+#             */
/*   Updated: 2025/08/16 00:23:49 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//stupid ai visualizer
/*void	cd_visualizer(t_pipeline *pl)
{
	printf("=== ENVIRONMENT VARIABLES ===\n");
	
	// Safety checks to prevent segfault
	if (!pl)
	{
		printf("ERROR: Pipeline is NULL\n");
		return;
	}
	
	if (!pl->env)
	{
		printf("ERROR: Environment list is NULL\n");
		return;
	}

	t_env_var *finger = pl->env;
	int count = 0;

	while (finger)
	{
		if (!finger->fullstring)
		{
			printf("WARNING: Empty environment variable at position %d\n", count);
		}
		else
		{
			printf("[%d] %s\n", count, finger->fullstring);
		}
		finger = finger->next;
		count++;
		
		// Safety check for infinite loops
		if (count > 500)
		{
			printf("ERROR: Too many environment variables (possible loop)\n");
			break;
		}
	}
	
	printf("=== TOTAL: %d variables ===\n", count);
}*/

void	old_pwd(t_pipeline *pl)
{
	t_env_var *finger = pl->env;
	char *current_pwd = get_env_value(pl->env, "PWD");
	
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
			return;
		}
		finger = finger->next;
	}
}

//on successful chdir it updates pwd
void	cd_update(t_pipeline *pl)
{
	t_env_var *finger = pl->env;
	char	cwd[PATH_MAX];

	old_pwd(pl);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return;
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
			return;
		}
		finger = finger->next;
	}
}

int cd_tracker(int argc, char **argv, t_pipeline *pl)
{
	//(void) pl; //FOR TEST EXISTING ELSE REM LINE
	if (ft_cd(argc, argv, pl) == 0)
	{
		//cd_visualizer(pl); //FOR TEST ELSE COMMENTED
		cd_update(pl);
		//cd_visualizer(pl);
		return (0);
	}
	else
	return (1);
}
