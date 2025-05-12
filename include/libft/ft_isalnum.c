/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:58:33 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/19 14:32:44 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}

// int	ft_isalpha(int c)
// {
// 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// 		return (1);
// 	else
// 		return (0);
// }
// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	else
// 		return (0);
// }
// int main(void)
// {
// 	char	test_cases[] = {'A', 'g', '1', '0', '9', '!', ' ', '\n'};
// 	int		num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
// 	printf("ft_isalnum:\n");
// 	for (int i = 0; i < num_cases; i++)
// 	{
// 		char c = test_cases[i];
// 		int result = ft_isalnum(c);
// 		printf("'%c' ascii value %d | ft_isalnum: %d\n",c, c, result);
// 	}
// 	return (0);
// }