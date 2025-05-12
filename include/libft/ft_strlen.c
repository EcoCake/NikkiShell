/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:23:29 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:24:59 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
// int	main(void)
// {
// 	const char *s1 = "Hello";
// 	const char *s2 = "";
// 	const char *s3 = " ";
// 	const char *s4 = "Hello, World!";
// 	const char *s5 = "1234567890";

// 	printf("Test 1: %zu (Expected: 5)\n", ft_strlen(s1));
// 	printf("Test 2: %zu (Expected: 0)\n", ft_strlen(s2));
// 	printf("Test 3: %zu (Expected: 1)\n", ft_strlen(s3));
// 	printf("Test 4: %zu (Expected: 13)\n", ft_strlen(s4));
// 	printf("Test 5: %zu (Expected: 10)\n", ft_strlen(s5)); 

// 	return (0);
// }
