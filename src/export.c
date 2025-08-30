/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:38:34 by sionow            #+#    #+#             */
/*   Updated: 2025/08/30 23:34:02 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expcounter(int argc, t_pipeline *pl)
{
	t_env_var	*finger;
	int			v;
	int			i;

	v = 0;
	i = 1;
	finger = pl->env;
	while (finger)
	{
		v++;
		finger = finger->next;
	}
	while (argc > 1 && i < argc)
	{
		v++;
		i++;
	}
	return (v);
}

void	expfiller(int argc, char **argv, char **exvar, t_pipeline *pl)
{
	t_env_var	*finger;
	int			e;
	int			i;

	e = 0;
	i = 1;
	finger = pl->env;
	while (finger)
	{
		if (ft_strchre(finger->fullstring, '=') == 0)
			exvar[e] = ft_strdupexp(finger->fullstring);
		else
			exvar[e] = ft_strdup(finger->fullstring);
		e++;
		finger = finger->next;
	}
	while (argc > 1 && i < argc)
	{
		if (ft_strchre(argv[i], '=') == 0)
			exvar[e] = ft_strdupexp(argv[i]);
		else
			exvar[e] = ft_strdup(argv[i]);
		e++;
		i++;
	}
}

void	expsorter(char **exvar)
{
	char	*temp;
	int		e;

	temp = NULL;
	e = 0;
	while (exvar[e])
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
	e = 0;
}

//shell == 0, exp == 1
int	exp_or_shell(char *arg)
{
	if (ft_strchre(arg, '=') == 0)
		return (1);
	else
		return (0);
}

int	ft_export(int argc, char **argv, t_pipeline *pl)
{
	char	**exvar;
	int		i;
	int		e;

	i = 0;
	e = expcounter(argc, pl);
	exvar = malloc(sizeof(char *) * (e + 1));
	pl->extcode = 0;
	if (!exvar)
		return (1);
	exvar[e] = NULL;
	expfiller(argc, argv, exvar, pl);
	expsorter(exvar);
	if (argc == 1)
		expprinter(exvar);
	while (argc > 1 && argv[i + 1])
	{
		i++;
		if (name_checker(argv[i], pl) == 1)
			continue ;
		dup_check(argv[i], pl);
	}
	ft_free(exvar);
	return (pl->extcode);
}
