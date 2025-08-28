/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:17:27 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 18:10:37 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_one_redir(t_redirection *redir, t_env_var *env, int status)
{
	char	*new_val;

	if (redir->type == HERE_DOC)
		return (0);
	new_val = expand_and_unquote(redir->file, env, status);
	if (!new_val)
	{
		perror("expansion: malloc failed");
		return (1);
	}
	free(redir->file);
	redir->file = new_val;
	return (0);
}

char	*str_append(char *dest, const char *src)
{
	char	*new_str;
	size_t	dest_len;
	size_t	src_len;

	dest_len = 0;
	if (dest)
		dest_len = ft_strlen(dest);
	src_len = 0;
	if (src)
		src_len = ft_strlen(src);
	new_str = malloc(dest_len + src_len + 1);
	if (!new_str)
	{
		if (dest)
			free(dest);
		return (NULL);
	}
	if (dest)
		ft_memcpy(new_str, dest, dest_len);
	if (src)
		ft_memcpy(new_str + dest_len, src, src_len);
	new_str[dest_len + src_len] = '\0';
	if (dest)
		free(dest);
	return (new_str);
}
