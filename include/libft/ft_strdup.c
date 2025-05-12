/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:49:14 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:41:12 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;

	dest = (char *) malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
// int	main(void)
// {
// 	// Test case 1: Normal string
// 	const char *str1 = "Hello, World!";
// 	char *dup1 = ft_strdup(str1);
// 	printf("Test 1: Original: '%s', Duplicated: '%s'\n", str1, dup1);
// 	free(dup1);
// 	// Test case 2: Empty string
// 	const char *str2 = "";
// 	char *dup2 = ft_strdup(str2);
// 	printf("Test 2: Original: '%s', Duplicated: '%s'\n", str2, dup2);
// 	free(dup2);
// 	// Test case 3: String with special characters
// 	const char *str3 = "Line1\nLine2\tTabbed!";
// 	char *dup3 = ft_strdup(str3);
// 	printf("Test 3: Original: '%s', Duplicated: '%s'\n", str3, dup3);
// 	free(dup3);
// return(0);
// }
