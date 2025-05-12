/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:48:56 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:42:20 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}
// int	main(void)
// {
// 	const char *s1 = "Hello";
// 	const char *s2 = "Hello";
// 	const char *s3 = "HelLo";
// 	const char *s4 = "Hell";
// 	const char *s5 = "Hello, World!";
// 	printf("Test 1: %d (Expected: 0)\n", ft_strncmp(s1, s2, 5));
// 	printf("Test 2: %d (Expected: >0)\n", ft_strncmp(s1, s3, 5));
// 	printf("Test 3: %d (Expected: <0)\n", ft_strncmp(s4, s1, 5));
// 	printf("Test 4: %d (Expected: 0)\n", ft_strncmp(s1, s5, 0));
// 	printf("Test 5: %d (Expected: 0)\n", ft_strncmp(s1, s2, 3));
// 	printf("Test 6: %d (Expected: <0)\n", ft_strncmp(s1, s5, 7)); 
// 	return (0);
// }
