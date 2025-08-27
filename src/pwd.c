/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:40:55 by sionow            #+#    #+#             */
/*   Updated: 2025/08/27 16:21:25 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//original error msg shows this second line: pwd: usage: pwd [-LP]
//but we dont have any flags pwd supports so no 2nd line

void	pwd_free(t_pipeline *pl)
{
	free(pl->pids);
	close_pipes(pl);
	free_cmd_list(pl->head);
	free_env_list(pl->env);
}

void	pwd_errormsg(char **argv)
{
	write(2, "pwd: ", 4);
	write(2, &argv[1][0], 1);
	write(2, &argv[1][1], 1);
	write(2, ": ", 2);
	write(2, "invalid option\n", 15);
}

int	ft_pwd(int argc, char **argv, t_pipeline *pl)
{
	char	cwd[PATH_MAX];

	if (argc > 1 && argv[1][0] == '-')
	{
		pwd_errormsg(argv);
		pwd_free(pl);
		exit(2);
	}
	else if ((argc == 1) || (argv[1][0] >= 32 && argv[1][0] <= 126))
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			write (1, cwd, ft_strlen(cwd));
			write(1, "\n", 1);
		}
		else
		{
			perror("pwd");
			return (2);
		}
		return (0);
	}
	return (2);
}
