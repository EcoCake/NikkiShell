/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 03:23:52 by sionow            #+#    #+#             */
/*   Updated: 2025/08/26 19:20:29 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	linesave_exit_free(t_pipeline *pl, t_cmd *cmds)
{
	free(pl->pids);
	close_pipes(pl);
	free_env_list(pl->env);
	free_cmd_list(cmds);
	close(pl->og_in);
	close(pl->og_out);
	exit(pl->extcode);
}

int	numchecker(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '-' || str[i] == '+') && ft_strlen(str) > 1)
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	line_saver1(t_pipeline *pl)
{
	pl->extcode = 2;
	printf("nikkishell: exit: : numeric argument required\n");
}

void	line_saver2(char **argv, t_pipeline *pl)
{
	printf("nikkishell: exit: %s: numeric argument required\n", argv[1]);
	pl->extcode = 2;
}

int	ft_exit(int argc, char **argv, t_pipeline *pl, t_cmd *cmds)
{
	printf("exit\n");
	if (argc == 1)
		exit(pl->extcode);
	else if (argc == 2 && argv[1][0] == '\0')
		line_saver1(pl);
	else if (argc == 2 && numchecker(argv[1]) == 0)
	{
		pl->extcode = ft_atoi(argv[1]);
		if (pl->extcode > 255)
			pl->extcode = pl->extcode % 256;
		else if (pl->extcode < 0)
			pl->extcode = ((pl->extcode % 256) + 256) % 256;
	}
	else if (argc > 2 && numchecker(argv[1]) == 0)
	{
		printf("nikkishell: exit: too many arguments\n");
		pl->extcode = 1;
		return (1);
	}
	else if (argc >= 2 && numchecker(argv[1]) == 1)
		line_saver2(argv, pl);
	linesave_exit_free(pl, cmds);
	exit(pl->extcode);
}
