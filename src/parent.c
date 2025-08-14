/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:31:38 by sionow            #+#    #+#             */
/*   Updated: 2025/08/14 22:39:19 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if its a builtin that needs a child or parent process
//child == 2 & parent == 0
int	adoption_center(t_cmd *cmds)
{

	if (((ft_strcmp(cmds->args[0], "echo") == 0)))
		return (2);
	if (((ft_strcmp(cmds->args[0], "pwd") == 0)))
		return (2);
	if (ft_strcmp(cmds->args[0], "env") == 0)
		return (2);
	if (ft_strcmp(cmds->args[0], "cd") == 0)
		return (0);
	if (ft_strcmp(cmds->args[0], "export") == 0)
		return (0);
	if (ft_strcmp(cmds->args[0], "unset") == 0)
		return (0);
	if (ft_strcmp(cmds->args[0], "exit") == 0)
		return (0);
	return (1);
}

int	builtin_check_parent(t_cmd *cmds)
{
	if (ft_strcmp(cmds->args[0], "cd") == 0)
		return (ft_cd(get_argc(cmds), cmds->args));
	return (127);
}
