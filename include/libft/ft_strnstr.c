/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:42:16 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:42:11 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (big[i] != '\0' && i < n)
	{
		while (big[i + j] == little[j] && big[i + j] && i + j < n)
		{
			j++;
			if (little[j] == 0)
				return ((char *) big + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
// int main(void)
// {
//printf("im so done, done = \"%s\"\n", ft_strnstr("im so done", "done", 12));
//printf("im so done, so = \"%s\"\n", ft_strnstr("im so done", "so", 5));
//printf("im so done, lo = \"%s\"\n", ft_strnstr("im so done", "lo", 10));
//printf("im so done, ! = \"%s\"\n", ft_strnstr("im so done", "!", 20));
//return 0;
// }