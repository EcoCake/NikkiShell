/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:22:09 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/26 15:15:32 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	if ((size_t)dest - (size_t) src < n)
	{
		i = n - 1;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
// int main(void)
// {
// 		char src[] = "I hope this works";
// 		char dest[20];
// 		ft_memmove(dest, src, 13);
// 		printf("no overlaps %s\n", dest);
// //===============================
// 		char str[] = "Please just work ill cry";
// 		ft_memmove(str + 6, str, 5);
// 		printf("src to dest overlapping %s\n", str);
// 	}