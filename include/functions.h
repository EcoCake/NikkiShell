/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:31:05 by amezoe            #+#    #+#             */
/*   Updated: 2025/07/29 22:11:17 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include "structs.h"
#include "minishell.h"

//  cd.c
int		ft_cd_error(char *path, char *to_free);
char	*ft_strjoinslash(char *s1, char *s2);
int		ft_path_extra(char *str);
int		ft_paths(char *str);
int		ft_cd(int argc, char **argv);

// echo.c

int		flag_checker(char *flag);
void	n_skipper(char **argv, int *j);
void	ft_write_lines(char **argv, int *i, int *j);
int		ft_echo(int argc, char **argv);

// env_utils.c

t_env_var	*create_env_node(char *env_str);
t_env_var	*init_env_list(char **envp);
char		*get_env_value(t_env_var *env_list, const char *key);
char		**env_list_array(t_env_var *env_list);

// exec.c

int		ft_strcmp(char *s1, char *s2);
void	free_tab_exec(char **tab);
void	exit_free(t_cmd *cmds);
char	**create_args(char *args1, char *args2);
void	fill_cmds(t_cmd **cmds);
int		cmds_count(t_cmd *cmds);
void	close_pipes(t_pipeline *pl);
void	init_pl(t_pipeline *pl, t_cmd *cmds, char **env);
void	command_redirections(int i, t_pipeline *pl, t_cmd *cmds);
int		absolute_path(char *cmd);
char	*env_path(t_cmd *cmds);
void	not_builtin(t_pipeline *pl, t_cmd *cmds);
int		get_argc(t_cmd *cmds);
int		builtin_check(t_pipeline *pl, t_cmd *cmds);
void	exec(t_pipeline *pl, t_cmd *cmds, int i);
void	command_loop(t_pipeline *pl, t_cmd *cmds);
void	exec_main(t_cmd *cmds, char **env);

//free.c

void	free_token_list(t_token *head);
void	free_env_list(t_env_var *head);
void	free_env_array(char **env_array);
void	free_str_array(char **array);
void	free_redir_list(t_redirection *head);
void	free_cmd_list(t_cmd *head);

// get_next_line_utils.c

int		ft_strchrnum(char *s, char c);
char	*ft_cpystr(char *s1);

// get_next_line.c

char	*ft_fill_ex(char *excess);
char	*ft_replace(char *excess, char *all);
char	*ft_readline(int fd, char *excess);
char	*get_next_line(int fd);

// parser_utils.c

t_redirection	*create_redir_node(t_token_types type, char *file);
int				add_redir_to_cmd(t_cmd *cmd, t_redirection *new_redir);
int				count_word_tokens(t_token *head);
char			**tokens_to_args_array(t_token **current_token);

// parser.c

t_cmd	*create_cmd_node();
t_cmd	*parse_tokens(t_token *tokens);

//redirs.c

void	read_until_limiter(int fd, char *limiter);
void	heredoc_check(t_cmd *cmds);
void	redir_in_check(t_cmd *cmds);
void	redir_out_check(t_cmd *cmds);
void	redir_append_check(t_cmd *cmds);

//signals.c

extern volatile sig_atomic_t g_last_signal;
void	handle_sigint_rl(int signal);

// tokenize_utils.c

int		is_space(int c);
int		skip_space(const char *line, int i);
int		is_quote(char c);
int		is_operator(char c);
int		is_word_char(char c);
int		is_word(const char *s);
char	*extract_word(const char *line, int *position);
char	*extract_quoted_str(const char *line, int *position, char quote);
char	*extract_file_delimiter(const char *line, int *position);

// tokenize.c

t_token_types	t_type(const char *str);
void			add_token(t_token **head, t_token **current, char *value, t_token_types type);
t_token			*tokenize(char *line);

#endif