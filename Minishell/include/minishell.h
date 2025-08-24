/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:45:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/24 14:37:32 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// ************************************************************************** //
//                                 Structures                                 //
// ************************************************************************** //

typedef struct s_token
{
	char				*value;
	int					type;
	int					quote_type;
	struct s_token		*next;
}						t_token;

typedef struct s_token_lst
{
	t_token				*head;
	t_token				*tail;
}						t_token_lst;

typedef struct s_redir
{
	int					type;
	char				*file;
	int					expand;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**argv;
	t_redir				*redir;
	struct s_command	*next;
}						t_command;

typedef struct s_shell
{
	char				**envp;
	int					exit_code;
	bool				should_exit;
}						t_shell;

typedef struct s_exec_context
{
	t_command			*cmd;
	t_shell				*state;
	int					prev_fd;
	int					pipe_fd[2];
	int					is_last;
}						t_exec_context;

typedef struct s_clean_state
{
	int					i;
	int					j;
	int					in_s_quote;
	int					in_d_quote;
}						t_clean_state;

typedef struct s_indices
{
	int					i;
	size_t				j;
}						t_indices;

// ************************************************************************** //
//                                Enumerations                                //
// ************************************************************************** //

enum					e_token_type
{
	WORD = 0,
	PIPE = 1,
	REDIRECT_IN = 2,
	REDIRECT_OUT = 3,
	APPEND_OUT = 4,
	HEREDOC = 5,
};

typedef enum e_quote_type
{
	DEFAULT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}						t_quote_type;

// ************************************************************************** //
//                                 Functions                                  //
// ************************************************************************** //

/* CORE --------------------------------------------------------------------- */

/* input.c */
char					*read_line_input(void);

/* LEXER -------------------------------------------------------------------- */

/* lexer.c */
t_token					*lexer(char *line);

/* lexer_handlers.c */
int						handle_word(t_token_lst *lst, char **c);
int						handle_single_op(t_token_lst *lst, char **c);
int						handle_double_op(t_token_lst *lst, char **c);

/* lexer_word_utils.c */
int						update_quote_state(char *word, int type, int i);
int						get_quote_type(char *word);
char					*find_word_end(char *word);

/* lexer_clean_word.c */
char					*extract_and_clean_word(const char *start, int len);

/* lexer_token_utils.c */
t_token					*create_token(t_token_lst *lst, char *word, int type,
							int quote_info);

void					print_tokens(t_token *head);
void					free_tokens(t_token *head);

/* EXPANSION ---------------------------------------------------------------- */

/* expansion.c */
int						expand_token(t_token *head, t_shell *state);
char					*expand_str(const char *value, t_shell *state);

/* expansion_len_utils.c */
size_t					calculate_expanded_len(const char *value,
							t_shell *state);

/* expansion_var_utils.c */
char					*get_var_name(const char *input, int *i_ptr);
int						is_valid_varname(char *name);

/* expansion_append_utils.c */
size_t					append_str_to_result(char *dest, const char *src,
							size_t j);

/* PARSER --------------------------------------------------------------------*/

/* parser.c */
t_command				*parser(t_token *token_lst, t_shell *state);

/* parser_list_utils.c */
t_command				*create_command(void);
void					add_redir_to_cmd(t_command *cmd, t_redir *new_redir);
int						count_commands(t_command *cmds);
int						has_pipe(t_command *cmds);
int						is_redirection(int type);

/* parser_free_utils.c */
void					free_commands(t_command *cmd_head);

/* EXECUTION ---------------------------------------------------------------- */

/* execution.c */
int						execute(t_command *cmds, t_shell *state);
void					run_child_process(t_command *cmd, t_shell *state);

/* execution_utils.c */
int						is_builtin(char *cmd);
int						is_directory(const char *path);
int						execute_builtin(char **argv, t_shell *state);
int						save_original_fds(int *stdin_save, int *stdout_save);
int						restore_original_fds(int stdin_save, int stdout_save);

/* pipeline.c */
int						execute_pipeline(t_command *cmds, t_shell *state);
void					run_pipeline_child(t_exec_context *ctx);

/* pipeline_utils.c */
void					setup_pipe_context(t_exec_context *ctx, t_command *cmd,
							t_shell *state, int prev_fd);
void					close_pipe_fds(int *prev_fd, int pipe_fd[2],
							int is_last);
int						create_pipe_if_needed(int pipe_fd[2], int is_last);
void					setup_input_output(int prev_fd, int pipe_fd[2],
							int is_last);

/* process_utils.c */
int						fork_and_handle_child(t_exec_context *ctx);
void					wait_for_child(pid_t pid, t_shell *state);

/* redirections.c */
int						apply_redirections(t_redir *redir, t_shell *state);

/* heredoc */
void					read_heredoc_input(int write_fd, t_redir *redir,
							t_shell *state);
int						handle_heredoc(t_redir *redir, t_shell *state);

/* path.c */
void					get_absolute_path(char **argv, t_shell *state);

/* env_utils.c */
int						get_env_len(char **envp);
char					**create_env_copy(char **envp);
char					**find_env_var(char **envp, const char *key);
char					*get_env_value(const char *name, char **envp);

/* env_set.c */
int						set_env_var(t_shell *state, const char *key,
							const char *value);

/* env_unset.c */
int						unset_env_var(t_shell *state, const char *key);

/* SIGNALS ------------------------------------------------------------------ */

/* signals.c */
void					signal_handler(int sig);
void					setup_interactive_signals(void);
void					setup_non_interactive_signals(void);
void					setup_child_signals(void);

/* BUILTINS ----------------------------------------------------------------- */

/* builtin_cd.c */
int						builtin_cd(char **argv, t_shell *state);

/* builtin_echo.c */
int						builtin_echo(char **argv);

/* builtin_env.c */
int						builtin_env(t_shell *state);

/* builtin_export.c */
int						builtin_export(char **argv, t_shell *state);

/* builtin_export_utils.c */
void					print_env_sorted(t_shell *state);

/* builtin_exit.c */
int						builtin_exit(char **argv, t_shell *state);

/* builtin_pwd.c */
int						builtin_pwd(void);

/* builtin_unset.c */
int						builtin_unset(char **argv, t_shell *state);

/* UTILS -------------------------------------------------------------------- */

void					display_title(void);
char					*build_prompt(void);

/* DEBUG -------------------------------------------------------------------- */

char					*get_type_name(int type);
char					*get_quote_name(int quote_type);
void					debug_print_tokens(t_token *head);

#endif
