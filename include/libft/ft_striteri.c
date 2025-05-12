/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:55:45 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/27 12:40:10 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
// int	main(void)
// {
// 	char str1[] = "hello world!";
// 	ft_striteri(str1, ft_toupper);
// 	printf("Test 1: %s (Expected: HELLO WORLD!)\n", str1);

// 	char str2[] = "HELLO WORLD!";
// 	ft_striteri(str2, ft_tolower);
// 	printf("Test 2: %s (Expected: hello world!)\n", str2);
// 	return(0);
// }
