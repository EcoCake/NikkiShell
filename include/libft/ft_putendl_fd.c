/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:06:00 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:32:24 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
// int	main(void)
// {
// 	printf("Testing with STDOUT:\n");
// 	ft_putendl_fd("Hello, World!", 1);
// 	ft_putendl_fd("42 is amazing!", 1);
// 	ft_putendl_fd("This is a test.", 1);
// 	return(0);
// }