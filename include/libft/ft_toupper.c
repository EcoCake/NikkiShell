/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:35:06 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/26 16:55:26 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}
// int main(void)
// {
// printf("'a' = '%c'\n", ft_toupper('a')); 
// printf("'z' = '%c'\n", ft_toupper('z'));
// printf("'A' = '%c'\n", ft_toupper('A')); 
// printf("'Z' = '%c'\n", ft_toupper('Z')); 
// printf("'m' = '%c'\n", ft_toupper('m'));  
// printf("'1' = '%c'\n", ft_toupper('1'));  
// printf("'!' = '%c'\n", ft_toupper('!'));
// printf("'\\n' = '%c'\n", ft_toupper('\n')); 
// return (0);
// }