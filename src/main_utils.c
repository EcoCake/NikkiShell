/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:43:26 by sionow            #+#    #+#             */
/*   Updated: 2025/08/31 00:40:27 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_line_whitespace(char **line, int *status, t_env_var *env)
{
	char	*ptr;

	*line = sig_interrupt(status, env);
	if (!*line)
		return (1);
	ptr = *line;
	while (*ptr)
	{
		if (!is_space((unsigned char)*ptr))
			return (0);
		ptr++;
	}
	return (1);
}

void	line_fail(t_env_var *env_list)
{
	printf("exit\n");
	free_env_list(env_list);
	rl_clear_history();
}

void	line_ext2(char *line, int *last_exit_status)
{
	free(line);
	*last_exit_status = 2;
}

void	bye_bye(char *line, t_env_var *env_list, int last_exit_status)
{
	free(line);
	printf("Bye bye\n");
	free_env_list(env_list);
	rl_clear_history();
	exit (last_exit_status);
}

char	*sig_interrupt(int *last_exit_status, t_env_var *env_list)
{
	char	*line;

	line = readline("nikkishell$ ");
	if (g_last_signal == SIGINT)
	{
		*last_exit_status = 130;
		g_last_signal = 0;
	}
	if (line == NULL)
	{
		line_fail(env_list);
		exit (*last_exit_status);
	}
	return (line);
}
