/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 23:59:53 by sionow            #+#    #+#             */
/*   Updated: 2025/08/20 03:34:55 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//return of unset not sure: my posix return 0 and no reply if invalid identifier
//net says above 0 and bash: unset: `123var': not a valid identifier

int	checker(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) == 1 || str[i] == '_'))
			return (idk);
		i++;
	}
	return (0);
}
//leave for tmrw to tired
void	unset_env(char *str, t_pipeline *pl)
{
	t_env_var	*finger;
	t_env_var	*temp;
	int	i;

	finger = pl->env;
	temp = finger;
	i = 0;
	while (finger->fullstring[i] != '=')
		i++;
	while (finger && strncmp(str, finger->fullstring, i) != 0)
		finger = finger->next;
	if (finger && strncmp(str, finger->fullstring, ft_strlen(str)) == 0)
	{
		temp = finger;
		finger = finger->next;
		free(temp);
		return (0);
	}
	return (idk);
		
}

int ft_unset(int argc, char **argv, t_pipeline *pl, t_cmd *cmds)
{
	int	i;

	i = 1;
	if (argc == 1)
		return (0);
	if (argc > 1)
	{
		while (i < argc)
		{
			if (checker(argv[i]) == 0)
				unset_env(argv[i], pl);
			i++;
		}
		return (0);
	}
}