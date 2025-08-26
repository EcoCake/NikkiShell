/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 21:54:34 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/26 21:34:31 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_append(char *dest, const char *src)
{
	char *new_str;
	size_t dest_len = 0;
	size_t src_len = 0;	
	if (dest)
		dest_len = ft_strlen(dest);
	if (src)
		src_len = ft_strlen(src);
	new_str = malloc(dest_len + src_len + 1);
	if (!new_str)
	{
		if (dest)
			free(dest);
		return NULL;
	}
	if (dest)
	{
		ft_memcpy(new_str, dest, dest_len);
		free(dest);
	}
	if (src)
		ft_memcpy(new_str + dest_len, src, src_len);
	new_str[dest_len + src_len] = '\0';
	return new_str;
}

char	*expand_variable(const char *str_after_dollar, t_env_var *env_list, int last_exit_status)
{
	int		var_name_len;
	char	*var_name = NULL;
	char	*value;

	if (!str_after_dollar || *str_after_dollar == '\0')
		return (ft_strdup("$"));
	if (*str_after_dollar == '?')
		return (ft_itoa(last_exit_status));
	else if (*str_after_dollar == '$')
		return (ft_itoa(getpid()));
	var_name_len = get_var_name_len(str_after_dollar);
	if (var_name_len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(str_after_dollar, 0, var_name_len);
	if (!var_name)
		return (NULL);
	value = get_env_value(env_list, var_name);
	free(var_name);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
	
}
char	*tilde_expansion(const char *str, t_env_var *env_list)
{
	char	*home_dir;

	if (!str || *str != '~')
		return (ft_strdup(str));
	if (str[1] == '\0')
	{
		home_dir = get_env_value(env_list, "HOME");
		if (home_dir)
			return(ft_strdup(home_dir));
		return (ft_strdup("~"));
	}
	else if (str[1] == '/')
	{
		home_dir = get_env_value(env_list, "HOME");
		if (home_dir)
			return (ft_strjoinslash(home_dir, (char *)(str + 2)));
		return (ft_strdup(str));
	}
	return (ft_strdup(str));
}

char    *expand_and_unquote(char *str, t_env_var *env_list, int last_exit_status)
{
	char	*final_str;
	char	*var_value;
	int		i;
	int		in_squote;
	int		in_dquote;

	if (!str)
		return (NULL);
	final_str = ft_strdup("");
	if (!final_str)
		return (NULL);
	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			i++;
			continue;
		}
		if (str[i] == '"' && !in_squote)
		{
			in_dquote = !in_dquote;
			i++;
			continue;
		}
		if (str[i] == '$' && !in_squote)
		{
			int var_len = get_var_name_len(&str[i + 1]);
			var_value = expand_variable(&str[i + 1], env_list, last_exit_status);
			if (!var_value)
			{
				free(final_str);
				return (NULL);
			}
			final_str = str_append(final_str, var_value);
			free(var_value);
			i += var_len + 1;
		}
		else
		{
			char temp_char_str[2] = {0};
			temp_char_str[0] = str[i];
			final_str = str_append(final_str, temp_char_str);
			i++;
		}
	}
	return (final_str);
}

void	expand_cmd_args(t_cmd *cmd, t_env_var *env_list, int last_exit_status)
{
	int		i = 0;
	char	*new_arg_value;
	if (!cmd || !cmd->args)
		return;
	while (cmd->args[i])
	{
		new_arg_value = expand_and_unquote(cmd->args[i], env_list, last_exit_status);
		if (new_arg_value)
		{
			free(cmd->args[i]);
			cmd->args[i] = new_arg_value;
		}
		else
		{
			perror("expansion: malloc failed");
			return;
		}
		i++;
	}
}

void	expand_redirs(t_cmd *cmd, t_env_var *env_list, int last_exit_status)
{
	t_redirection	*current_redir;
	char			*new_file_value;
	if (!cmd || !cmd->redirection)
		return;
	current_redir = cmd->redirection;
	while (current_redir)
	{
		if (current_redir->type == HERE_DOC)
		{
			current_redir = current_redir->next;
			continue;
		}
		new_file_value = expand_and_unquote(current_redir->file, env_list, last_exit_status);
		if (new_file_value)
		{
			free(current_redir->file);
			current_redir->file = new_file_value;
		}
		else
		{
			perror("expansion: malloc failed");
			return;
		}
		current_redir = current_redir->next;
	}
}
