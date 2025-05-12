/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:47:22 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/26 15:15:51 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = malloc(size * nmemb);
	if (!ret)
		return (NULL);
	ft_bzero(ret, size * nmemb);
	return (ret);
}
//======================//
// void ft_bzero(void *s, size_t n) {
// 	char *str = (char *)s;
// 	while (n > 0) {
// 		*str = 0;
// 		str++;
// 		n--;
// 	}
// }
// int main(void)
// {
// 	size_t nmemb = 5;
// 	size_t size = sizeof(int);
// 	int *arr = (int *)ft_calloc(nmemb, size);
// 	if (arr == NULL) {
// 		printf("malloc fail\n");
// 		return 1;
// 	}
// 	size_t i = 0;
// 	while (i < nmemb) {
// 		if (arr[i] != 0) {
// 			printf("array %zu is not zero\n", i);
// 		free(arr);
// 			return 1;
// 		}
// 		i++;
// 	}
// 	printf("memory allocated and initialized to 0.\n");
// 	free(arr);
// 	return 0;
// }