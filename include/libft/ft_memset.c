/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:27:09 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:57:20 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = (unsigned char)c;
	return (s);
}
// int	main(void)
// {
// 	char buffer1[20] = "Hello, World!";
// 	char buffer2[20] = "Hello, World!";
// 	char buffer3[20] = "Hello, World!";
// 	char buffer4[20] = "1234567890";
// 	char buffer5[20] = "";
// 	ft_memset(buffer1, 'X', 5);
// 	printf("Test 1: '%s' (Expected: 'XXXXX, World!')\n", buffer1);
// 	ft_memset(buffer2, 'A', 13);
// 	printf("Test 2: '%s' (Expected: 'AAAAAAAAAAAAA')\n", buffer2);
// 	ft_memset(buffer3, '1', 7);
// 	printf("Test 3: '%s' (Expected: '1111111, World!')\n", buffer3);
// 	ft_memset(buffer4, '\0', 5);
// 	printf("Test 4: '%s' (Expected: '\\0\\0\\0\\0\\067890')\n", buffer4);
// 	ft_memset(buffer5, 'Z', 0);
// 	printf("Test 5: '%s' (Expected: '')\n", buffer5);
// 	return (0);
// }
