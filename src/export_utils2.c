/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:47:19 by sionow            #+#    #+#             */
/*   Updated: 2025/08/30 01:02:15 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expprinter(char **exvar)
{
	int		i;

	i = 0;
	while (exvar[i])
	{
		printf("export %s\n", exvar[i]);
		i++;
	}
}

void	exp_error_msg(char *var)
{
	write(2, "nikkishell: export: `", 21);
	write(2, var, ft_strlen(var));
	write(2, "': not a valid identifier", 25);
	write(2, "\n", 1);
}

int	name_checker(char *var, t_pipeline *pl)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[0]) == 0 && var[0] != '_')
	{
		exp_error_msg(var);
		pl->extcode = 1;
		return (1);
	}
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!(ft_isalnum(var[i]) == 1 || var[i] == '_'))
		{
			exp_error_msg(var);
			pl->extcode = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	dup_check(char *var, t_pipeline *pl)
{
	t_env_var	*f;
	int			i;

	f = pl->env;
	i = 0;
	while (f)
	{
		i = ft_strchrn(f->fullstring, '=');
		if (i == -1)
			i = ft_strchrn(var, '=') - 1;
		if (i >= 0 && ft_strncmp(f->fullstring, var, i) == 0)
		{
			if (ft_strchrn(var, '=') == -1)
				return ;
			free(f->fullstring);
			f->fullstring = ft_strdup(var);
			return ;
		}
		f = f->next;
	}
	add_env_var(var, pl);
}
