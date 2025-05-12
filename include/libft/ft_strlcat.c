/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:43:44 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:57:00 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		src_len;
	size_t		dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		dst_len = size;
	if (dst_len == size)
		return (size + src_len);
	if (src_len < size - dst_len)
		ft_memcpy (dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}
// int	main(void)
// {

// 	char buffer1[20] = "Hello";
// 	char buffer2[10] = "Hello";
// 	char buffer3[6] = "Hello";
// 	char buffer4[20] = "";
// 	char buffer5[10] = "Test";

// 	const char *src = " World";

// 	printf("Test 1: %zu (Expected: 11)\n", 
//ft_strlcat(buffer1, src, sizeof(buffer1)));
// 	printf("Resulting buffer1: '%s'\n", buffer1);
// 	printf("Test 2: %zu (Expected: 11)\n",
// ft_strlcat(buffer2, src, sizeof(buffer2)));
// 	printf("Resulting buffer2: '%s'\n", buffer2);
// 	printf("Test 3: %zu (Expected: 11)\n",
// ft_strlcat(buffer3, src, sizeof(buffer3)));
// 	printf("Resulting buffer3: '%s'\n", buffer3);
// 	printf("Test 4: %zu (Expected: 6)\n",
// ft_strlcat(buffer4, "World", sizeof(buffer4)));
// 	printf("Resulting buffer4: '%s'\n", buffer4);
// 	printf("Test 5: %zu (Expected: 9)\n", 
//ft_strlcat(buffer5, "ing", sizeof(buffer5)));
// 	printf("Resulting buffer5: '%s'\n", buffer5);
// 	return (0);
// }