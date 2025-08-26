/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:29:52 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/25 12:26:14 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <sys/types.h>


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


typedef struct s_pipeline
{
	t_env_var 	*env;
	t_cmd		*head;
	int			**pipes;
	pid_t		*pids;
	int			num_cmds;
	int			num_pids;
	int			p_m;
	int			extcode;
	int			og_in;
	int			og_out;
}	t_pipeline;

//for norminette i need extra struct

typedef struct s_tokenize_context
{
	t_token	**head;
	t_token	**current;
	char	*line;
	int		*i;
} t_tokenize_context;

#endif