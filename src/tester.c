/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:17:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/06/03 14:16:57 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char		*line;
	t_token 	*tokens;
	t_token 	*temp;
	t_env_var	*env_list;

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
				temp = tokens;
				printf("tokens \n");
				while (temp)
				{
					printf ("type %d, value '%s'\n", temp->type, temp->value);
					temp = temp->next;
				}
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
	return (0);
}

