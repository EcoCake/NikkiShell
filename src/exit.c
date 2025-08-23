/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 03:23:52 by sionow            #+#    #+#             */
/*   Updated: 2025/08/23 03:41:44 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	numchecker(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
//quuits when too many args after returning success
//exit "" , - and + should exit numeric req (2) but just quits w 0

int	ft_exit(int argc, char **argv, t_pipeline *pl)
{
	printf("exit\n");
	if (argc == 1)
		exit(0);
	else if(argc == 2 && numchecker(argv[1]) == 0)
	{
		pl->extcode = ft_atoi(argv[1]);
		if (pl->extcode > 255)
			pl->extcode = pl->extcode % 256;
		else if (pl->extcode < 0)
			pl->extcode = ((pl->extcode % 256) + 256) % 256;//wtf
	}
	else if (argc > 2 && numchecker(argv[1]) == 0)
	{
		printf("exit: too many arguments\n");
		pl->extcode = 1; //dont exit
		printf("aaa");
		return (1); //?
	}
	else if (argc >= 2 && numchecker(argv[1]) == 1)
	{
		printf("exit: %s: numeric argument required\n", argv[1]);
		pl->extcode = 2;
	}
	exit(pl->extcode);
}
