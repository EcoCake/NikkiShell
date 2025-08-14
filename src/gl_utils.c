/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:50:09 by sionow            #+#    #+#             */
/*   Updated: 2025/07/26 18:18:22 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchrnum(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_cpystr(char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	if (!s1[i])
		return (NULL);
	while (s1[i + 1] && s1[i + 1] != '\n')
		i++;
	s2 = malloc(i + 2);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i + 1] && s1[i + 1] != '\n')
	{
		s2[i] = s1[i];
		i++;
	}
	if (s1[i + 1] == '\n')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
