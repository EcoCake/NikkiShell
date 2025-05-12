/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:03:23 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:36:24 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
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