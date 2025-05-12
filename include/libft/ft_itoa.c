/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:50:27 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/25 16:06:39 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numb_len(int numb)
{
	int	len;

	len = 0;
	if (numb <= 0)
		len++;
	while (numb)
	{
		len++;
		numb = numb / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	numb;

	len = ft_numb_len(n);
	numb = n;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (numb < 0)
	{
		str[0] = '-';
		numb = -numb;
	}
	if (numb == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (numb)
	{
		str[len] = numb % 10 + '0';
		len--;
		numb = numb / 10;
	}
	return (str);
}

// int main()
// {
// 	printf("%s\n", ft_itoa(0-0));
// 	printf("%s\n", ft_itoa(987654321));
// 	printf("%s\n", ft_itoa(-123456789));
// }
