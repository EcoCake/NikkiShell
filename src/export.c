
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

int expcounter(int argc, t_pipeline *pl)
{
	t_env_var *finger;
	int v;
	int	i;
	
	v = 0;
	i = 1;
	finger = pl->env;
	while (finger)
	{
		if (ft_strchre(finger->fullstring, '=') == 0)
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

char	*ft_strdupexp(const char *s)
{
	char	*dup;
	int		i;
	int		j;
	int		equal;

	dup = malloc(ft_strlen(s) + 3);
	i = 0;
	j = 0;
	equal = 0;
	while (s[i])
	{
		dup[j] = s[i];
		if (equal == 0 && s[i] == '=')
		{
			equal = 1;
			j++;
			dup[j] = '"';
		}
		j++;
		i++;
	}
	dup[j] = '"';
	dup[j + 1] = '\0';
	return (dup);
}

void	expfiller(int argc, char **argv, char **exvar, t_pipeline *pl)
{
	t_env_var *finger;
	int e;
	int	i;
	
	e = 0;
	i = 1;
	finger = pl->env;
	while (finger)
	{
		if (ft_strchre(finger->fullstring, '=') == 0)
		{
			exvar[e] = ft_strdupexp(finger->fullstring);
			e++;
		}
		finger = finger->next;
	}
	while (argc > 1 && i < argc)
	{
		exvar[e] = ft_strdupexp(argv[i]);
		e++;
		i++;
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

//shell == 0, exp == 1
int	exp_or_shell(char *arg)
{
	if (ft_strchre(arg, '=') == 0)
		return (1);
	else
		return (0);
}

void add_env_var(char *var, t_pipeline *pl)
{
    t_env_var *new = create_env_node(var);
    t_env_var *curr;

    if (!new)
        return ;
    curr = pl->env;
	while (curr->next)
    curr = curr->next;
    curr->next = new;
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

int ft_strchrn(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	name_checker(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[0]) == 0 && var[0] != '_')
	{
		write(2, "export: ", 8);
		write(2, var, ft_strlen(var));
		write(2, ": not a valid identifier", 24);
		write(2, "\n", 1);
		return (1);
	}
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!(ft_isalnum(var[i]) == 1 || var[i] == '_'))
		{
			write(2, "export: ", 8);
			write(2, var, ft_strlen(var));
			write(2, ": not a valid identifier", 24);
			write(2, "\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	dup_check(char *var, t_pipeline *pl)
{
	t_env_var *f;
	int	i;

	f = pl->env;
	i = 0;
	while (f)
	{
		i = ft_strchrn(f->fullstring, '=');
		if (i >= 0 && ft_strncmp(f->fullstring, var, i) == 0)
		{
			free(f->fullstring);
			f->fullstring = ft_strdup(var);
			return ;
		}
		f = f->next;
	}
	add_env_var(var, pl);
}

int ft_export(int argc, char **argv, t_pipeline *pl)
{
	
	char 	**exvar;
	int		i;
	int		e;
	
	i = 0;
	e = expcounter(argc, pl);
	exvar = malloc(sizeof(char *) * (e + 1));
	if (!exvar)
		return (1); // Put 1 instead of nothing, since it will serve as the error_code
	exvar[e] = NULL;
	expfiller(argc, argv, exvar, pl); // Added argv to the parameters
	expsorter(exvar);
	if (argc == 1)
		expprinter(exvar);
	while (argc > 1 && argv[i + 1])
	{
		i++;
		if (name_checker(argv[i]) == 1)
			continue ;
		if (exp_or_shell(argv[i]) == 1)
			dup_check(argv[i], pl);
	}
	ft_free(exvar);
	return (0);
} 
