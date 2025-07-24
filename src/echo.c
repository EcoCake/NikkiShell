#include "minishell.h"

//0 = no flag, 1 = flag found
int	flag_checker(char *flag)
{
	int	i;

	if (flag[0] != '-' || flag[1] != 'n')
		return (0);
	i = 2;
	while (flag[i] != '\0')
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	n_skipper(char **argv, int *j)
{
	while (argv[*j] && flag_checker(argv[*j]) == 1)
		(*j)++;
}

void	ft_write_lines(char **argv, int *i, int *j)
{
	(*i) = 0;
	while (argv[*j][*i])
	{
		write (1, &argv[*j][*i], 1);
		(*i)++;
	}
	if (argv[*j + 1])
		write (1, " ", 1);
	(*j)++;
}

//int f = flag. if 0 no flag, if 1 flag
int	ft_echo(int argc, char **argv)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	j = 2;
	f = 0;
	if (argc > 2)
	{
		if (flag_checker(argv[2]) == 1)
		{
			f = 1;
			j++;
		}
		if (argc > 3)
			n_skipper(argv, &j);
		while (argv[j])
			ft_write_lines(argv, &i, &j);
		if (f == 0)
			write (1, "\n", 1);
	}
	else
		write (1, "\n", 1);
	return (0);
}
