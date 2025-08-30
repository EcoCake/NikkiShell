/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:10:24 by sionow            #+#    #+#             */
/*   Updated: 2025/08/30 23:09:02 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*increment_shell_lvl(char *str)
{
	char	*new;
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	temp = ft_strdup("SHLVL=");
	temp2 = ft_itoa(ft_atoi(&str[i]) + 1);
	new = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (new);
}
