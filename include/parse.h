/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:18:37 by amezoe            #+#    #+#             */
/*   Updated: 2025/05/14 22:25:29 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h> // if vs code gives error, install sudo apt-get install libreadline-dev 
//for readline u need all from stdio, readline, and history.

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

int	is_space(int c);
int	skip_space(char *line, int i);
int	is_quote(char c);
int	is_word_char(char c);
int	is_word(const char *s);

//tokenize.c

t_token_types	t_type(const char *str);
void add_token(t_token **head, t_token **current, char *value, t_token_types type);

#endif
