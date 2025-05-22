/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:18:37 by amezoe            #+#    #+#             */
/*   Updated: 2025/05/22 15:44:01 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../include/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>

//work in progress struct, as far as ive seen this should be
//sufficient enough. goes 0 to 8 

typedef enum e_token_types
{
	D_QUOTE,
	QUOTE,
	HERE_DOC,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	WORD
}	t_token_types;

typedef struct s_token
{
	char			*value;
	t_token_types	type;
	struct s_token	*next; //linked list of tokens
}	t_token;

//tokenize_utils.c
//super self explanatory

//TODO fix smth grisha said was wrong

int	is_space(int c);
int	skip_space(char *line, int i);
int	is_quote(char c);
int	is_word_char(char c);
int	is_word(const char *s);

//tokenize.c

t_token_types	t_type(const char *str);
void add_token(t_token **head, t_token **current, char *value, t_token_types type);


//signals

extern volatile sig_atomic_t g_last_signal;

void handle_sigint_rl(int signal);

#endif
