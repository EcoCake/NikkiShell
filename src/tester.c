/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:17:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/07/24 13:49:08 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	
	char		*line;
	t_token 	*tokens;
	t_token		*temp_token_print;
	t_env_var	*env_list;
	t_cmd		*commands;

	signal(SIGINT, handle_sigint_rl); // handler for sigint ctrl c
	//when received func will be called
	signal(SIGQUIT, SIG_IGN); // ignore ctrl 

	env_list = init_env_list(envp);
	if (!env_list)
	{
		printf("cant init env\n");
		return(1);
	}
	
	while(1)
	{
		g_last_signal = 0;
		line = readline("nikkishell$ ");
		if (g_last_signal != 0)
		{
			if (line)
				free(line);
			continue;
		}
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (*line)
		{
			if (ft_strncmp("exit", line, 5) == 0)
			{
				free(line);
				printf("Bye bye\n");
				free_env_list(env_list);
				rl_clear_history();
				return 0;
			}
			add_history(line);
			printf("You entered '%s'\n", line);

			//test for env_list
			printf("home: %s\n", get_env_value(env_list, "HOME"));
			printf("path: %s\n", get_env_value(env_list, "PATH"));
			//smol test for not existing value
			char *nonextist_value = NULL;
			nonextist_value = get_env_value(env_list, "DOENSTEXIST");
			if (nonextist_value)
				printf("doesnt exist: %s\n", nonextist_value);
			else
				printf("doenst exist: null\n");

			
			tokens = tokenize(line);
			if (tokens)
			{
				temp_token_print = tokens;
				printf("-------tokens--------\n");
				while (temp_token_print)
				{
					printf ("type %d, value '%s'\n", temp_token_print->type, temp_token_print->value);
					temp_token_print = temp_token_print->next;
				}
				printf ("----------------\n");
				
				commands = parse_tokens(tokens);
				if (!commands)
				{
					printf("cant parse tokens\n");
					free_token_list(tokens);
					free(line);
					continue;
				}

				printf("-------parsed command-----\n");
				
				t_cmd *cmd_temp = commands;
				while (cmd_temp)
				{
					printf("commands block: \n"); //print arg array
					if (cmd_temp->args)
					{
						int i = 0;
						printf (" ARGS: [");
						while (cmd_temp->args[i])
						{
							printf (" '%s'", cmd_temp->args[i]);
							i++;
							if (cmd_temp->args[i])
								printf(", ");
						}
						printf ("]\n");
					}
					else
						printf ("No args found\n");
					// print redir list

					if (cmd_temp->redirection)
					{
						t_redirection *redir_tmp = cmd_temp->redirection;
						printf(" REDIRECTIONS:    \n");
						while (redir_tmp)
						{
							printf ("   Type: %d (FILE: '%s')\n", redir_tmp->type, redir_tmp->file);
							redir_tmp = redir_tmp->next;
						}
					}
					else
						printf (" No redirections\n");
					cmd_temp = cmd_temp->next;
					if (cmd_temp)
						printf(" ----- PIPE TO NEXT CMD-----\n");
				}
				
				free_cmd_list(commands);
				free_token_list(tokens);
			}
			else 
				printf("error with tokenizing\n");
		}
		else
			printf("You entered an empty line\n");
		free(line);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	free_env_list(env_list);
	rl_clear_history();
	
	return (0);
}

