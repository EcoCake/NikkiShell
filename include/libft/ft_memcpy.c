/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:33:52 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/25 20:03:06 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest != src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;
// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }
// int main(void)
// {
// 	char src1[] = "i wanna end it please";
// 	char src2[] = "so happy to live";
// 	char dest1[50];
// 	char dest2[50];
// 	size_t first = ft_strlen(src1) + 1;
// 	size_t second = 8;
// 	printf("first string is '%s'\n", src1);
// 	printf("copying %zu bytes\n", first);
// 	ft_memcpy(dest2, src2, second);
// 	printf("second string is '%s'\n", dest2);
// 	ft_memcpy(dest1, src1, first);
// 	return(0);
// }
