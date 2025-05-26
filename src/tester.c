/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:17:16 by amezoe            #+#    #+#             */
/*   Updated: 2025/05/26 14:10:11 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"


int main()
{
	char *line;

	t_token *tokens;
	t_token *temp;

	signal(SIGINT, handle_sigint_rl); // handler for sigint ctrl c
	//when received func will be called
	signal(SIGQUIT, SIG_IGN); // ignore ctrl\ 

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
				rl_clear_history();
				return 0;
			}
			add_history(line);
			printf("You entered '%s'\n", line);

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

