/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:04:24 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/26 15:16:15 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_bzero(void *s, size_t n)
// {
// 	char	*str;

// 	str = (char *) s;
// 	while (n > 0)
// 	{
// 		*str = 0;
// 		str++;
// 		n--;
// 	}
// }

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void	*ret;

// 	ret = malloc(size * nmemb);
// 	if (!ret)
// 		return (NULL);
// 	ft_bzero(ret, size * nmemb);
// 	return (ret);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len])
// 		len++;
// 	return (len);
// }
// char	*ft_strdup(const char *s)
// {
// 	char	*dest;
// 	size_t	i;

// 	dest = (char *) malloc(ft_strlen(s) + 1);
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		dest[i] = s[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

static char	*ft_newstring(const char *s1, size_t start, size_t length)
{
	char	*str;
	size_t	i;

	if (length == 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	str = ft_calloc(length + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < length)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_trim(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && ft_trim(set, s1[start]))
		start++;
	while (end > start && ft_trim(set, s1[end - 1]))
		end--;
	return (ft_newstring(s1, start, end - start));
}

// int main(void)
// {
// 	char	*result;
// 	result = ft_strtrim("  How many times do i have to fix ", " ");
// 	printf("trimmed stuff '%s'\n", result);
// 	free(result);
// 	result = ft_strtrim("", " ");
// 	printf("trimmed stuff '%s'\n", result);
// 	free(result);
// }