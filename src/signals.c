/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:16:57 by amezoe            #+#    #+#             */
/*   Updated: 2025/05/26 14:11:29 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

volatile sig_atomic_t g_last_signal = 0;

void handle_sigint_rl(int signal)
{
	g_last_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}