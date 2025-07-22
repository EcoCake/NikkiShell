/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:18:37 by amezoe            #+#    #+#             */
/*   Updated: 2025/06/15 13:31:56 by amezoe           ###   ########.fr       */
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
	D_QUOTE,			//0
	QUOTE,				//1
	HERE_DOC,			//2
	PIPE,				//3
	REDIR_IN,			//4
	REDIR_OUT,			//5
	REDIR_APPEND,		//6
	WORD,				//7
	DEFAULT_ERROR		//8
}	t_token_types;

// struct redirection {
// 	char *filename;			hihi
// 	t_token_types type;		REDIR_IN
// }


// struct for the environment variable
//this was my original idea but due to export ill parse as whole
//string
// typedef struct s_env_var
// {
// 	char				*key; //example USER or HOME etc
// 	char				*value; // whatever comes after key
// 	struct s_env_var	*next; // pointer to next var in the list
// } t_env_var;


typedef struct s_env_var
{
	char				*fullstring; // stores key=value as whole
	struct s_env_var	*next;
} t_env_var;

typedef struct s_token
{
	char			*value;
	t_token_types	type;
	struct s_token	*next; //linked list of tokens
}	t_token;

//struct for a single redir
typedef struct s_redirection
{
	t_token_types			type; //redirIn,redirOut etc
	char					*file;
	struct s_redirection	*next;
}	t_redirection;


//struc for command

typedef struct s_cmd
{
	char			**args; // array of strings for cmd name and args for execve
	t_redirection 	*redirection;
	struct s_cmd	*next;
} t_cmd;

//tokenize_utils.c
//super self explanatory

//parser_utils

t_redirection	*create_redir_node(t_token_types type, char *file);
int	add_redir_to_cmd(t_cmd *cmd, t_redirection *new_redir);
int count_word_tokens(t_token *head);
char	**tokens_to_args_array(t_token **current_token);

//parser

t_cmd *create_cmd_node();
t_cmd *parse_tokens(t_token *tokens);



//TODO sort funcs according to norm, im sorry im lazy asf

int	is_space(int c); //this ok
int	is_operator(char c); //this ok
int	skip_space(const char *line, int i);
int	is_quote(char c); //is ok
int	is_word_char(char c);
int	is_word(const char *s);
char *extract_word(const char *line, int *position);
char *extract_quoted_str(const char *line, int *position, char quote);
char *extract_file_delimiter(const char *line, int *position);

// env_utils.c

t_env_var	*create_env_node(char *env_str);
t_env_var	*init_env_list(char **envp);
char		*get_env_value(t_env_var *env_list, const char *key);
char		**env_list_array(t_env_var *env_list);

//tokenize.c

t_token_types	t_type(const char *str);
void add_token(t_token **head, t_token **current, char *value, t_token_types type);
t_token *tokenize(char *line);

//signals

extern volatile sig_atomic_t g_last_signal;
void handle_sigint_rl(int signal);

//free.c

void	free_token_list(t_token *head);
void	free_env_list(t_env_var *head);
void	free_env_array(char **env_array);
void free_str_array(char **array);
void free_redir_list(t_redirection *head);
void free_cmd_list(t_cmd *head);


#endif
