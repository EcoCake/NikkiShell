/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:50:12 by sionow            #+#    #+#             */
/*   Updated: 2025/07/23 13:08:20 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_fill_ex(char *excess)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (excess[i] != '\n' && excess[i])
		i++;
	if (!excess[i])
	{
		free(excess);
		return (NULL);
	}
	next_line = malloc(ft_strlen(excess) - i + 1);
	i++;
	while (excess[i])
	{
		next_line[j++] = excess[i++];
	}
	next_line[j] = '\0';
	free(excess);
	return (next_line);
}

char	*ft_replace(char *excess, char *all)
{
	char	*join;

	join = ft_strjoin(excess, all);
	free(excess);
	return (join);
}

char	*ft_readline(int fd, char *excess)
{
	char	*all;
	int		endcheck;

	all = malloc(BUFFER_SIZE + 1);
	all[0] = '\0';
	if (!excess)
	{
		excess = malloc(1);
		excess[0] = '\0';
	}
	endcheck = 1;
	while (endcheck != 0 && ft_strchrnum(all, '\n')
		!= 1 && ft_strchrnum(excess, '\n') != 1)
	{
		endcheck = read (fd, all, BUFFER_SIZE);
		if (endcheck < 0)
		{
			free(all);
			return (NULL);
		}
		all[endcheck] = '\0';
		excess = ft_replace(excess, all);
	}
	free (all);
	return (excess);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*excess;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	excess = ft_readline(fd, excess);
	if (!excess)
		return (NULL);
	line = ft_cpystr(excess);
	excess = ft_fill_ex(excess);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);
// 	return (0);
// }