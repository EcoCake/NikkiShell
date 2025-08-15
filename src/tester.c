/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:17:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/16 00:11:34 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char		*line;
	t_token		*tokens;
	t_env_var	*env_list;
	t_cmd		*commands;
	int			last_exit_status = 0; // <<< LOCAL VARIABLE FOR $?
	signal(SIGINT, handle_sigint_rl); // Handler for SIGINT (Ctrl+C)
	signal(SIGQUIT, SIG_IGN);        // Ignore SIGQUIT (Ctrl+\)
	env_list = init_env_list(envp);
	if (!env_list)
	{
		printf("cannot initialize environment\n");
		return(1);
	}
	while(1)
		{
			if (g_last_signal != 0)
			{
				//f a SIGINT occurred, bash typically sets $? to 130 (128 + SIGINT).
				if (g_last_signal == SIGINT)
					last_exit_status = 130;

				g_last_signal = 0;
				}
			line = readline("nikkishell$ ");
			if (g_last_signal != 0)
			{
				if (line) // readline allocates memory so free it if a signal interrupted it
					free(line);
				if (g_last_signal == SIGINT)
					last_exit_status = 130;
				g_last_signal = 0;
				continue;
			}
			if (line == NULL)// EOF Ctrl d detected
			{
				printf("exit\n");
				break;
			}
			if (*line)
			{
				if (ft_strncmp("exit", line, 5) == 0 && (line[4] == '\0' || is_space(line[4])))
				{
					free(line);
					printf("Bye bye\n");
					free_env_list(env_list);
					rl_clear_history();
					//return last_exit_status if 'exit' is the cmd without arg
					return last_exit_status; 
				}
				add_history(line);
				// Original printfs for testing env_list and tokens (can remove in final)
				// printf("You entered '%s'\n", line);
				// printf("home: %s\n", get_env_value(env_list, "HOME"));
				// printf("path: %s\n", get_env_value(env_list, "PATH"));
				// char *nonextist_value = get_env_value(env_list, "DOENSTEXIST");
				// if (nonextist_value) printf("doesnt exist: %s\n", nonextist_value);
				// else printf("doenst exist: null\n");
				tokens = tokenize(line);
				if (!tokens) // Error during tokenization (e.g., unclosed quote)
				{
					// fprintf(stderr, "minishell: syntax error during tokenization\n"); // tokenizer already prints errors
					free(line);
					last_exit_status = 2; // Set exit status for syntax error
					continue;
				}
				// Original token printing (can remove in final)
				// t_token *temp_token_print = tokens;
				// printf("-------tokens--------\n");
				// while (temp_token_print) {
				//     printf ("type %d, value '%s'\n", temp_token_print->type, temp_token_print->value);
				//     temp_token_print = temp_token_print->next;
				// }
				// printf ("----------------\n");
				commands = parse_tokens(tokens);
				free_token_list(tokens);
				if (!commands) // Error during parsing (e.g., syntax error with pipes/redirs)
				{
					// printf("cant parse tokens\n"); // Your parser already prints errors
					free(line);
					last_exit_status = 2; // Set exit status for parsing error
					continue;
				}
				// Original parsed command printing (can remove in final)
				// printf("-------parsed command-----\n");
				// t_cmd *cmd_temp = commands;
				// while (cmd_temp) {
				//     printf("commands block: \n");
				//     if (cmd_temp->args) {
				//         int i = 0; printf (" ARGS: ["); while (cmd_temp->args[i]) { printf (" '%s'", cmd_temp->args[i]); i++; if (cmd_temp->args[i]) printf(", "); } printf ("]\n");
				//     } else printf ("No args found\n");
				//     if (cmd_temp->redirection) {
				//         t_redirection *redir_tmp = cmd_temp->redirection; printf(" REDIRECTIONS:    \n"); while (redir_tmp) { printf ("   Type: %d (FILE: '%s')\n", redir_tmp->type, redir_tmp->file); redir_tmp = redir_tmp->next; }
				//     } else printf (" No redirections\n");
				//     cmd_temp = cmd_temp->next;
				//     if (cmd_temp) printf(" ----- PIPE TO NEXT CMD-----\n");
				// }
				// <<< CALL EXEC_MAIN WITH THE POINTER TO last_exit_status >>>
				exec_main(commands, env_list); 
				free_cmd_list(commands); // Free the command structure after execution
			}
			// else
			//    printf("You entered an empty line\n"); // Can comment out if not desired
			free(line);
		}
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		free_env_list(env_list);
		rl_clear_history();
		
		return (last_exit_status);
	}
