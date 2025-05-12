/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:12:26 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/26 16:10:50 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

// int main(void)
// {
// 	const char *str = "End my suffering";
// 	char *result = ft_strchr(str, 'm');
// 	if (result)
// 		printf(" m is at %ld position\n", result - str);
// 	else 
// 		printf("char not found in string\n");
// 	return (0);
// }