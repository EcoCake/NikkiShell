/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 00:35:40 by sionow            #+#    #+#             */
/*   Updated: 2025/08/21 15:49:48 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strchre(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int expcounter(t_pipeline *pl)
{
	t_env_var *finger;
	int v;
	
	v = 0;
	finger = pl->env;
	while (finger)
	{
		if (ft_strchre(finger->fullstring, '=') == 0)
			v++;
		finger = finger->next;
	}
	return (v);
}

void	expfiller(char **exvar, t_pipeline *pl)
{
	t_env_var *finger;
	int e;
	
	e = 0;
	finger = pl->env;
	while (finger)
	{
		if (ft_strchre(finger->fullstring, '=') == 0)
		{
			exvar[e] = ft_strdup(finger->fullstring);
			e++;
		}
		finger = finger->next;
	}
}

void expsorter(char **exvar)
{
	char *temp;
	int	e;

	temp = NULL;
	e = 0;
	while(exvar[e])
	{
		if (exvar[e + 1] && ft_strcmp(exvar[e], exvar[e + 1]) > 0)
		{
			temp = exvar[e];
			exvar[e] = exvar[e + 1];
			exvar[e + 1] = temp;
			e = 0;
		}
		else
			e++;
	}
}

void exp_alone(t_pipeline *pl)
{
	char 	**exvar;
	int		e;
	
	e = expcounter(pl);
	exvar = malloc(sizeof(char *) * (e + 1));
	if (!exvar)
		return ;
	expfiller(exvar, pl);
	expsorter(exvar);
	exvar[e] = NULL;
}

int ft_export(int argc, t_pipeline *pl)
{
	if (argc == 1)
	{
		exp_alone(pl);
	}
	return (0);
} 
