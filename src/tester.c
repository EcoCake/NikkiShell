/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:17:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/26 20:17:01 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_line_whitespace(const char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (!is_space((unsigned char)*line))
			return (0);
		line++;
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char        *line;
	t_token     *tokens;
	t_env_var   *env_list;
	t_cmd       *commands;	
	int         last_exit_status = 0;
		
		// Signal handling
	signal(SIGINT, handle_sigint_rl);
	signal(SIGQUIT, SIG_IGN);
		
	env_list = init_env_list(envp);
	if (!env_list)
	{
		printf("cannot initialize environment\n");
		return(1);
	}	
    while(1)
    {
        if (g_last_signal == SIGINT)
        {
            last_exit_status = 130;
            g_last_signal = 0;
        }
        line = readline("nikkishell$ ");    
        // this is where it was bad, if readline is null then exit it handles both ctrld d and c and cuckblocks readline
        if (line == NULL)
        {
            printf("exit\n");
            break;
        }
		if (is_line_whitespace(line))
		{
			free(line);
			continue;
		}
        if (g_last_signal == SIGINT)
		{
            free(line);
            continue;
        }
		if (*line)
		{
			if (ft_strncmp("exit", line, 5) == 0 && (line[4] == '\0' || is_space(line[4])))
			{
				free(line);
				printf("Bye bye\n");
				free_env_list(env_list);
				rl_clear_history();
				return last_exit_status;
			}
			add_history(line);
			tokens = tokenize(line);
			if (!tokens)
			{
				free(line);
				last_exit_status = 2;
				continue;
			}
			commands = parse_tokens(tokens);
			free_token_list(tokens);
			if (!commands)
			{
				free(line);
				last_exit_status = 2;
				continue;
			}
			//make the expansion on all args and redirs before exec
			expand_cmd_args(commands, env_list, last_exit_status);
			expand_redirs(commands, env_list, last_exit_status);
			//exec command which has the expanded args
			last_exit_status = exec_main(commands, env_list);

			free_cmd_list(commands);
		}
		free(line);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	free_env_list(env_list);
	rl_clear_history();
		
	return (last_exit_status);
}