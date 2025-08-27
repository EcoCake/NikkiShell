/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:31:05 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/27 15:27:21 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include "structs.h"
#include "minishell.h"

//  cd.c
int		ft_path_extra(char *str, t_pipeline *pl);
int		ft_paths(char *str);
void	linesavercd(t_pipeline *pl, char *path);
int		ft_cd(int argc, char **argv, t_pipeline *pl);

//	cd_utils.c
int		ft_cd_error(char *path, char *to_free);
char	*fill_path(char *str);
int		error_msg_cd(void);
char	*ft_strjoinslash(char *s1, char *s2);

// echo.c
int		flag_checker(char *flag);
void	n_skipper(char **argv, int *j);
void	ft_write_lines(char **argv, int *i, int *j);
int		ft_echo(int argc, char **argv);

// pwd.c
void	pwd_free(t_pipeline *pl);
void	pwd_errormsg(char **argv);
int 	ft_pwd(int argc, char **argv, t_pipeline *pl);

// env.c
int	ft_env(int argc, char **argv, t_pipeline *pl);

//	unset.c
int		unset_head(char *str, t_pipeline *pl);
void	unset_last(char *str, t_pipeline *pl);
void	unset_env(char *str, t_pipeline *pl);
int		ft_unset(int argc, char **argv, t_pipeline *pl);

//	export.c
void 	exp_alone(t_pipeline *pl);
void 	expsorter(char **exvar);
void	expfiller(int argc, char **argv, char **exvar, t_pipeline *pl);
int 	expcounter(int argc, t_pipeline *pl);
int 	ft_export(int argc, char **argv, t_pipeline *pl);

//	export_utils.c
int 	ft_strchre(char *str, char c);
char	*ft_strdupexp(const char *s);
void	ft_free(char **array);
int		ft_strchrn(char *str, char c);
void	add_env_var(char *var, t_pipeline *pl);

//	export_utils2.c
void	expprinter(char **exvar);
int		name_checker(char *var);
void	dup_check(char *var, t_pipeline *pl);

//	exit.c
void	linesave_exit_free(t_pipeline *pl, t_cmd *cmds);
int		numchecker(char *str);
void	line_saver1(t_pipeline *pl);
void	line_saver2(char** argv, t_pipeline *pl);
int		ft_exit(int argc, char **argv, t_pipeline *pl, t_cmd *cmds);

// env_utils.c

t_env_var	*create_env_node(char *env_str);
t_env_var	*init_env_list(char **envp);
char		*get_env_value(t_env_var *env_list, const char *key);
char		**env_list_array(t_env_var *env_list);

//	parent.c
int		adoption_center(t_cmd *cmds);
void	exec_parent(t_pipeline *pl, t_cmd *cmds, int i);
void	restore_fds(int save_fd_in, int save_fd_out, char *cmds, t_cmd *cm);
int		children_counter(t_cmd *cmds);
void	child_exec(t_pipeline *pl, t_cmd *cur_cmd, int i);

//	env_update.c
void	old_pwd(t_pipeline *pl);
void	strjoin_fail_msg(t_env_var	*finger);
void	cd_update(t_pipeline *pl);
int		cd_tracker(int argc, char **argv, t_pipeline *pl);

// exec.c
void	redir_loop(t_cmd *cmds, t_pipeline *pl, int i);
void	command_redirections(int i, t_pipeline *pl, t_cmd *cmds, int parent);
void	exec(t_pipeline *pl, t_cmd *cmds, int i);
void	command_loop(t_pipeline *pl, t_cmd *cmds);
int		exec_main(t_cmd *cmds, t_env_var *env_list, int last_exit_status);

// exec_utils.c
int		get_argc(t_cmd *cmds);
int		ft_strcmp(char *s1, char *s2);
void	free_tab_exec(char **tab);
void	exit_free(t_cmd *cmds);
int		cmds_count(t_cmd *cmds);

//	exec_path.c
int		absolute_path(char *cmd);
char	*env_path(t_cmd *cmds, t_pipeline *pl);

//	exec_pipes.c
void	close_pipes(t_pipeline *pl);
void	init_pl(t_pipeline *pl, t_cmd *cmds, t_env_var *env_list);
void	init_pipes(t_pipeline *pl, int num_cmds);

//	exec_builtins.c
char	*join3(char *s1, char *s2, char *s3);
void	not_builtin(t_pipeline *pl, t_cmd *cmds);
int		builtin_check(t_pipeline *pl, t_cmd *cmds);

//free.c

void	free_token_list(t_token *head);
void	free_env_list(t_env_var *head);
void	free_env_array(char **env_array);
void	free_str_array(char **array);
void	free_redir_list(t_redirection *head);
void	free_cmd_list(t_cmd *head);

// parser_utils.c

t_redirection	*create_redir_node(t_token_types type, char *file);
int				add_redir_to_cmd(t_cmd *cmd, t_redirection *new_redir);
int				count_word_tokens(t_token *head);
char			**tokens_to_args_array(t_token **current_token);

// parser.c

t_cmd	*create_cmd_node();
t_cmd	*parse_tokens(t_token *tokens);

//heredoc.c
int		read_until_limiter(int fd, char *limiter);
void	heredoc_exit(t_cmd *cmds, t_pipeline *pl, int fd);
void	heredoc_check(t_cmd *cmds, t_pipeline *pl);

//redirs.c
void	redir_in_check(t_pipeline *pl, t_redirection *f);
void	redir_out_check(t_pipeline *pl, t_redirection *f);
void	redir_append_check(t_pipeline *pl, t_redirection *f);

//signals.c

extern volatile sig_atomic_t g_last_signal;
void	handle_sigint_rl(int signal);
void	signalhandler(int sig);

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

//expansion.c

int		is_var_char(char c);
int 	get_var_name_len(const char *s);
char	*str_append(char *dest, const char *src);
char	*expand_variable(const char *str_after_dollar, t_env_var *env_list, int last_exit_status);

//does the ~expansion (~, ~/path), returns the allocated str with the expanded path
char *tilde_expansion(const char *str, t_env_var *env_list);

//this processes  the str (token value or redir filename), it goes thru the str, handles the quotes and does the expansion and then builds a new str without the quotes
char	*expand_and_unquote(char *str, t_env_var *env_list, int last_exit_status);

// goes thru the t_cmd->args and puts the expansions and unquotation on each arg. it replaces the og expanded str and frees the old
void	expand_cmd_args(t_cmd *cmd, t_env_var *env_list, int last_exit_status);

//goes thru the t_cmd->redirection list and puts the expansion and unquote to the file part of each redir node
void	expand_redirs(t_cmd *cmd, t_env_var *env_list, int last_exit_status);

#endif