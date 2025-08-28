/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:29:52 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 19:22:45 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/types.h>

typedef enum e_token_types
{
	D_QUOTE,
	QUOTE,
	HERE_DOC,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	WORD,
	DEFAULT_ERROR
}	t_token_types;

typedef struct s_env_var
{
	char				*fullstring;
	struct s_env_var	*next;
}	t_env_var;
typedef struct s_token
{
	char			*value;
	t_token_types	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection
{
	t_token_types			type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_cmd
{
	char			**args;
	t_redirection	*redirection;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipeline
{
	t_env_var		*env;
	t_cmd			*head;
	int				**pipes;
	pid_t			*pids;
	int				num_cmds;
	int				num_pids;
	int				p_m;
	int				extcode;
	int				og_in;
	int				og_out;
}	t_pipeline;

typedef struct s_exp_ctx
{
	char			*str;
	t_env_var		*env;
	int				las;
	int				i;
	int				in_squote;
	int				in_dquote;
}	t_exp_ctx;

typedef struct s_tokenizer_state
{
	t_token				*head;
	t_token				*current;
	char				*line;
	int					i;
}	t_tokenizer_state;

#endif
