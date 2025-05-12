/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:31:47 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:56:09 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str != NULL)
	{
		ft_strlcpy(str, s1, len + 1);
		ft_strlcat(str, s2, len +1);
	}
	return (str);
}
// int	main(void)
// {
// 	const char *s1 = "Hello";
// 	const char *s2 = " World!";
// 	const char *s3 = "";
// 	const char *s4 = "42";
// 	const char *s5 = NULL;
// 	char *result = ft_strjoin(s1, s2);
// 	printf("Test 1: '%s' + '%s' = '%s' ('Hello World!')\n", s1, s2, result);
// 	free(result);
// 	result = ft_strjoin(s1, s3);
// 	printf("Test 2: '%s' + '%s' = '%s' ('Hello')\n", s1, s3, result);
// 	free(result);
// 	result = ft_strjoin(s3, s2);
// 	printf("Test 3: '%s' + '%s' = '%s' (' World!')\n", s3, s2, result);
// 	free(result);
// 	return(0);
// }
