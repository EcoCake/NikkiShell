/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:56:37 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/19 14:31:47 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// int main(void)
// {
// 	char	test_cases[] = {'A', 'g', '1', '0', '9', '!', ' ', '\n'};
// 	int		num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
// 	printf("ft_isdigit:\n");
// 	for (int i = 0; i < num_cases; i++)
// 	{
// 		char c = test_cases[i];
// 		int result = ft_isdigit(c);
// 		printf("'%c' ascii value %d | ft_isdigit: %d\n",c, c, result);
// 	}
// 	return (0);
// }