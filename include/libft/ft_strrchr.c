/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:43:28 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:55:15 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char*s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
// int main(void)
// {
//printf("Hello, World!, 'o' = \"%s\"\n", ft_strrchr("Hello, World!", 'o'));
//printf("abcdabcd, 'c' = \"%s\"\n", ft_strrchr("abcdabcd", 'c'));
//printf("'a' \"%s\"\n", ft_strrchr("", 'a'));
//printf("abcdabcd, '\\0' = \"%s\"\n", ft_strrchr("abcdabcd", '\0'));
//return 0;
// }