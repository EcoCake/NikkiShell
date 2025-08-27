/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:03:23 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/27 16:05:52 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s)
	{
		i = ft_strlen(s);
		write(fd, s, i);
	}
}
// int	main(void)
// {
// 	ft_putstr_fd("Hello, World!\n", 1);
// 	ft_putstr_fd("42 is amazing!\n", 1);
// 	ft_putstr_fd("This is a test string.\n", 1);
// 	ft_putstr_fd("", 1); // Empty string
// 	ft_putstr_fd("End of STDOUT test.\n", 1);
// 	return(0);
// }