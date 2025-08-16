/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:40:55 by sionow            #+#    #+#             */
/*   Updated: 2025/08/17 01:07:07 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//original error msg shows this second line: pwd: usage: pwd [-LP]
//but we dont have any flags pwd supports so no 2nd line
void	pwd_errormsg(char **argv)
{
		write(2, "pwd: ", 4);
		write(2, &argv[1][0], 1);
		write(2, &argv[1][1], 1);
		write(2, ": ", 2);
		write(2, "invalid option\n", 15);
}

int ft_pwd(int argc, char **argv, t_cmd *cmds)
{
	if (argc > 1 && argv[1][0] == '-')
	{
		pwd_errormsg(argv);
		exit_free(cmds);
		exit(2);
	}
	else if ((argc == 1) || (argv[1][0] >= 32 && argv[1][0] <= 126))
	{
		char	cwd[PATH_MAX];
		
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
