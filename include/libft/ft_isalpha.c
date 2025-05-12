/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:48:13 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/19 14:32:14 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

// int main(void)
// {
// 	char	test_cases[] = {'A', 'g', '1', '0', '9', '!', ' ', '\n'};
// 	int		num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
// 	printf("ft_isalpha:\n");
// 	for (int i = 0; i < num_cases; i++)
// 	{
// 		char c = test_cases[i];
// 		int result = ft_isalpha(c);
// 		printf("'%c' ascii value %d | ft_isalpha: %d\n",c, c, result);
// 	}
// 	return (0);
// }