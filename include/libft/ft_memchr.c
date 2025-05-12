/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:17:42 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/25 20:02:22 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
// int main(void)
// {
// 	const char str[] = "This should work";
// 	int to_find = 's';
// 	size_t bytes = 20;

// 	char *result = (char *)ft_memchr(str, to_find, bytes);
// 	if (result != NULL)
// 		printf("character '%c' found at pos %ld", to_find , result - str + 1);
// 	else
// 		printf("char '%c' cant be found", to_find);
// }
