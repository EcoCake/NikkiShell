/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:40:55 by sionow            #+#    #+#             */
/*   Updated: 2025/08/03 18:07:57 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(int argc)
{
	if (argc == 1)
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
			return (1);
		}
		return (0);
	}
	return (1);
}