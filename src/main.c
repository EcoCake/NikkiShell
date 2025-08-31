/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:50:38 by sionow            #+#    #+#             */
/*   Updated: 2025/08/31 00:21:31 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*env_check(char **env)
{
	t_env_var	*list;

	list = init_env_list(env);
	if (!list)
	{
		printf("cannot initialize environment\n");
		exit(1);
	}
	return (list);
}

int	check_tok(char *line, t_token **tok, t_env_var *env, int *exit_status)
{
	if (ft_strncmp("exit", line, 5) == 0 && (line[4] == '\0'
			|| is_space(line[4])))
		bye_bye(line, env, *exit_status);
	add_history(line);
	*tok = tokenize(line);
	if (!*tok)
	{
		line_ext2(line, exit_status);
		return (0);
	}
	return (1);
}

int	check_cmds(t_cmd **cmds, t_token *tok, int *exit_status, char *line)
{
	*cmds = parse_tokens(tok);
	free_token_list(tok);
	if (!*cmds)
	{
		line_ext2(line, exit_status);
		return (0);
	}
	return (1);
}

void	expand_and_exec(t_cmd *cmds, t_env_var *env_list, int *status)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		expand_cmd_args(tmp, env_list, *status);
		tmp = tmp->next;
	}
	expand_redirs(cmds, env_list, *status);
	*status = exec_main(cmds, env_list, *status);
	free_cmd_list(cmds);
}

int	main(int ac, char **av, char **envp)
{
	t_env_var	*env;
	int			status;

	char *(line) = NULL;
	t_token *(tok) = NULL;
	t_cmd *(cmds) = NULL;
	sig_change(&status, ac, av);
	env = env_check(envp);
	while (1)
	{
		if (is_line_whitespace(&line, &status, env) || g_last_signal == SIGINT)
		{
			free(line);
			continue ;
		}
		if (*line)
		{
			if (!check_tok(line, &tok, env, &status)
				|| !check_cmds(&cmds, tok, &status, line))
				continue ;
			expand_and_exec(cmds, env, &status);
		}
		free(line);
	}
	return (status);
}
