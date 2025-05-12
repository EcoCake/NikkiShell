/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:44:43 by amezoe            #+#    #+#             */
/*   Updated: 2024/11/16 18:09:32 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long			result;
	long			sign;
	unsigned int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return ((int)(result * sign));
}

// int main(void)
// {
// 	const char *empty = "";
// 	const char *negative = "-125654";
// 	const char *invalid = "swdfsdf5669";
// 	const char *edgecase = "-0";
// 	const char *positive = "+658654";

// 	printf("empty '%s' -- %d\n", empty, ft_atoi(empty));
// 	printf("negative '%s' -- %d\n", negative, ft_atoi(negative));
// 	printf("invalid '%s' -- %d\n", invalid, ft_atoi(invalid));
// 	printf("edgecase '%s' -- %d\n", edgecase, ft_atoi(edgecase));
// 	printf("positive '%s' -- %d\n", positive, ft_atoi(positive));

// 	return (0);
// }