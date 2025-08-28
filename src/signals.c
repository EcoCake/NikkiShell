/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:16:57 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 18:05:06 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

void	sig_change(int *last_exit_status, int ac, char **av)
{
	(void)ac;
	(void)av;
	signal(SIGINT, handle_sigint_rl);
	signal(SIGQUIT, SIG_IGN);
	*last_exit_status = 0;
}

void	signalhandler(int sig)
{
	if (sig == SIGINT)
	{
		g_last_signal = SIGINT;
	}
}

void	handle_sigint_rl(int signal)
{
	g_last_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
