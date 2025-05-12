/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:30:35 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/26 15:18:08 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t n)
{
	size_t	src_length;
	size_t	i;

	src_length = ft_strlen(src);
	if (n > 0)
	{
		i = 0;
		while (i < n - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_length);
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
// 	char dest[20];
// 	const char *src = "Should be okay";
// 	size_t copied;
// 	copied = ft_strlcpy(dest, src, sizeof(dest));
// 	printf("copied %zu destination '%s", copied, dest);
// 	return (0);
// }