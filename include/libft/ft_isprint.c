/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:19:33 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/19 14:31:29 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

// int main(void)
// {
// 	char	test_cases[] = {'A', 'g', '1', '0', '9', '!', ' ', '\n'};
// 	int		num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
// 	printf("ft_isprint:\n");
// 	for (int i = 0; i < num_cases; i++)
// 	{
// 		char c = test_cases[i];
// 		int result = ft_isprint(c);
// 		printf("'%c' ascii value %d | ft_isprint: %d\n",c, c, result);
// 	}
// 	return (0);
// }