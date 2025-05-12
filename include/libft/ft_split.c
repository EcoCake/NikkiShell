/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:00:23 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/26 16:26:45 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countwords(const char *str, char c)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (str[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

char	*cpystr(const char *s, int start, int end)
{
	char	*tab;
	int		i;
	int		j;

	tab = malloc((end - start + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
	{
		tab[j] = s[i];
		j++;
		i++;
	}
	tab[j] = '\0';
	return (tab);
}

void	free_tab(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**assign_strings(char **tab, const char *s, char c)
{
	int	i;
	int	start;
	int	index;

	i = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			tab[index] = cpystr(s, start, i);
			if (!tab[index])
				return (free_tab(tab, index), NULL);
			index++;
		}
		else
			i++;
	}
	tab[index] = NULL;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		words;

	if (!s)
		return (NULL);
	words = countwords(s, c);
	tab = malloc((words + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	return (assign_strings(tab, s, c));
}

// int	main(void)
// {
// 	int		i;
// 	char	**tab;

// 	i = 0;
// 	tab = ft_split("  He llo            Wo rld", ' ');
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }