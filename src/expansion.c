/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 21:54:34 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 14:26:40 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(const char *str_dllr, t_env_var *env_list, int las)
{
	int		var_name_len;
	char	*var_name;
	char	*value;

	var_name = NULL;
	if (!str_dllr || *str_dllr == '\0')
		return (ft_strdup("$"));
	if (*str_dllr == '?')
		return (ft_itoa(las));
	else if (*str_dllr == '$')
		return (ft_itoa(getpid()));
	var_name_len = get_var_name_len(str_dllr);
	if (var_name_len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(str_dllr, 0, var_name_len);
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
			return (ft_strdup(home_dir));
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

void	expand_cmd_args(t_cmd *cmd, t_env_var *env_list, int last_exit_status)
{
	int		i;
	char	*new_arg_value;

	i = 0;
	if (!cmd || !cmd->args)
		return ;
	while (cmd->args[i])
	{
		new_arg_value = expand_and_unquote(cmd->args[i],
				env_list, last_exit_status);
		if (new_arg_value)
		{
			free(cmd->args[i]);
			cmd->args[i] = new_arg_value;
		}
		else
		{
			perror("expansion: malloc failed");
			return ;
		}
		i++;
	}
}

void	expand_redirs(t_cmd *cmd, t_env_var *env_list, int last_exit_status)
{
	t_redirection	*current_redir;

	if (!cmd || !cmd->redirection)
		return ;
	current_redir = cmd->redirection;
	while (current_redir)
	{
		if (process_one_redir(current_redir, env_list, last_exit_status) != 0)
			return ;
		current_redir = current_redir->next;
	}
}
