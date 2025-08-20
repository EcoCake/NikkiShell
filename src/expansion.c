/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 21:54:34 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/19 21:00:00 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
int get_var_name_len(const char *s)
{
	int i;
	i = 0;

	if (s[i] == '?' || s[i] == '$')
		return 1;
	while (s[i] && is_var_char(s[i]))
		i++;
	return i;
}
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
	int     var_name_len;
	char    *var_name = NULL;
	char    *value;
	
	if (!str_after_dollar || *str_after_dollar == '\0')
		return(ft_strdup("$"));
	if (*str_after_dollar == '?')
		return(ft_itoa(last_exit_status));
	else if (*str_after_dollar == '$')
		return (ft_itoa(getpid()));
	var_name_len = get_var_name_len(str_after_dollar);
	if (var_name_len == 0)
		return(ft_strdup("$"));
	var_name = ft_substr(str_after_dollar, 0, var_name_len);
	if (!var_name)
		return NULL;
	value = get_env_value(env_list, var_name);
	free(var_name);
	if (value)
		return (ft_strdup(value));
	else
		return(ft_strdup(""));
}

char *tilde_expansion(const char *str, t_env_var *env_list)
{
	char *home_dir;
	if (!str || *str != '~')
		return (ft_strdup(str)); // no ~ to expand
	if (str[1] == '\0')
	{
		home_dir = get_env_value(env_list, "HOME");
		if (home_dir)
			return(ft_strdup(home_dir));
		return (ft_strdup("~")); // if no home set just ~
	}
//this is terrible but hear me out
	else if (str[1] == '/')
	{
		home_dir = get_env_value(env_list, "HOME");
		if (home_dir)
			return (ft_strjoinslash(home_dir, (char *)(str + 2)));
		return (ft_strdup(str));
	}
	return  (ft_strdup(str)); // returm original string for unhandled ~
}

char *expand_and_unquote(char *str, t_env_var *env_list, int last_exit_status)
{
    char *expanded_result = ft_strdup("");
    int i = 0;
    int quote_state = 0;
    char *temp_segment;

    if (!str || !expanded_result)
        return (NULL);

    while (str[i])
    {
        if (str[i] == '\'' && quote_state == 0)
        {
            quote_state = 1;
            i++;
        }
        else if (str[i] == '\"' && quote_state == 0)
        {
            quote_state = 2;
            i++;
        }
        else if ((str[i] == '\'' && quote_state == 1) || (str[i] == '\"' && quote_state == 2))
        {
            quote_state = 0;
            i++;
        }
        else if (str[i] == '$' && quote_state != 1)
        {
            i++;
            int var_name_length = get_var_name_len(str + i);
            temp_segment = expand_variable(str + i, env_list, last_exit_status);
            if (!temp_segment)
            {
                free(expanded_result);
                return NULL;
            }
            expanded_result = str_append(expanded_result, temp_segment);
            free(temp_segment);
            i += var_name_length;
        }
        else
        {
            char current_char[2];
            current_char[0] = str[i];
            current_char[1] = '\0';
            expanded_result = str_append(expanded_result, current_char);
            if (!expanded_result)
                return NULL;
            i++;
        }
    }
    return expanded_result;
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
		else //here i dont know if we need to free already expanded args and the command lists so i just return, we will have to see if its gonna be incomplete expansion or no
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
	while (current_redir)//HEREDOC DELIMITERS ARE NOT TO BE EXPANDED
	{
		if (current_redir->type == HERE_DOC)
		{
			current_redir = current_redir->next;
			continue; //skip expansion for heredoc delimiter
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
