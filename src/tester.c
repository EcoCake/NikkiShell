/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:17:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/27 16:09:03 by amezoe           ###   ########.fr       */
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
        // Get user input first.
        line = readline("nikkishell$ ");    

        // If readline was interrupted by Ctrl+C, the flag will be set.
        // We MUST update the status now, before processing the new line.
        if (g_last_signal == SIGINT)
        {
            last_exit_status = 130;
            g_last_signal = 0;
        }

        // Now handle Ctrl+D (EOF)
        if (line == NULL)
        {
            printf("exit\n");
            free_env_list(env_list);
            rl_clear_history();
            return (last_exit_status); 
        }

        // Now handle empty/whitespace lines
        if (is_line_whitespace(line))
        {
            free(line);
            continue;
        }
        
        // From here on, last_exit_status is guaranteed to be up-to-date.
        if (*line)
        {
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

            // Expansion will now use the correct, updated status
            expand_cmd_args(commands, env_list, last_exit_status);
            expand_redirs(commands, env_list, last_exit_status);
            
            last_exit_status = exec_main(commands, env_list, last_exit_status);
            free_cmd_list(commands);
        }
        free(line);
    }
    return (last_exit_status); // This line is effectively unreachable
}