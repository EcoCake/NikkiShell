/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:34:51 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/19 14:21:15 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*string;
	unsigned int	i;

	string = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (s[i])
	{
		string[i] = f(i, s[i]);
		i++;
	}
	string[i] = '\0';
	return (string);
}

// int	ft_toupper(int c)
// {
// 	if (c >= 97 && c <= 122)
// 		c -= 32;
// 	return (c);
// }

// int main()
// {
// 	char *s = "i wanna die";
// 	char *result;

// 	result = ft_strmapi(s, ft_toupper(s));
// 	if (result)
// 	{
// 		printf("%s", s);
// 		printf("%s", result);
// 		free (result);
// 	}
// 	else 
// 	{
// 		printf("Malloc fail");
// 	}
// 	return (0);
// }