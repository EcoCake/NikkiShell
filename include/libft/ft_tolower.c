/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:44:24 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/26 16:40:24 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
// int main(void)
// {
// printf("'a' = '%c'\n", ft_tolower('a')); 
// printf("'z' = '%c'\n", ft_tolower('z'));
// printf("'A' = '%c'\n", ft_tolower('A')); 
// printf("'Z' = '%c'\n", ft_tolower('Z')); 
// printf("'m' = '%c'\n", ft_tolower('m'));  
// printf("'1' = '%c'\n", ft_tolower('1'));  
// printf("'!' = '%c'\n", ft_tolower('!'));
// printf("'\\n' = '%c'\n", ft_tolower('\n')); 
// return (0);
// }