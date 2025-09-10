/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:45:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/10 14:38:23 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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
# include "libft.h"

// ************************************************************************** //
//                                 Global Variable                            //
// ************************************************************************** //

extern volatile sig_atomic_t	g_exit_status;
extern volatile sig_atomic_t	g_signal_received;

// ************************************************************************** //
//                                 Structures                                 //
// ************************************************************************** //

typedef struct s_token
{
	char						*value;
	int							type;
	int							quote_type;
	struct s_token				*next;
}								t_token;

typedef struct s_token_lst
{
	t_token						*head;
	t_token						*tail;
}								t_token_lst;

typedef struct s_redir
{
	int							type;
	char						*file;
	int							expand;
	struct s_redir				*next;
	int							is_heredoc;
	char						tmp_name[64];
}								t_redir;

typedef struct s_command
{
	char						**argv;
	t_redir						*redir;
	struct s_command			*next;
}								t_command;

typedef struct s_shell
{
	char						**envp;
	int							exit_code;
	bool						should_exit;
}								t_shell;

typedef struct s_exec_context
{
	t_command					*cmd;
	t_shell						*state;
	int							prev_fd;
	int							pipe_fd[2];
	int							is_last;
}								t_exec_context;

typedef struct s_clean_state
{
	int							i;
	int							j;
	int							in_s_quote;
	int							in_d_quote;
}								t_clean_state;

typedef struct s_indices
{
	int							i;
	size_t						j;
}								t_indices;

// ************************************************************************** //
//                                Enumerations                                //
// ************************************************************************** //

enum							e_token_type
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
}								t_quote_type;

// ************************************************************************** //
//                            Functions Prototypes                            //
// ************************************************************************** //

/* MAIN & CORE LOOP---------------------------------------------------------- */
void							init_shell_state(t_shell *state, char **envp);
void							prompt_loop(t_shell *state);
void							parse_and_execute(t_shell *state, char *line);
char							*read_line_input(void);
char							*build_prompt(void);

/* PARSING -------------------------------------------------------------------*/

/* Syntax & Lexer */
int								has_unclosed_quotes(char *line);
t_token							*lexer(char *line);
int								handle_double_op(t_token_lst *lst, char **c);
int								handle_single_op(t_token_lst *lst, char **c);
int								handle_word(t_token_lst *lst, char **c);
char							*find_word_end(char *word);
char							*extract_and_clean_word(const char *start,
									int len);
int								get_quote_type(char *word);
int								update_quote_state(char *word, int type, int i);
t_token							*create_token(t_token_lst *lst, char *word,
									int type, int quote_info);
void							free_tokens(t_token *head);
/* Expansion */
int								expand_token(t_token *head, t_shell *state);
char							*expand_str(const char *value, t_shell *state);
void							expand_exit_status(char *dest, size_t *j,
									t_shell *state);
void							expand_pid(char *dest, size_t *j);
void							expand_regular_var(const char *src, char *dest,
									t_indices *indices, t_shell *state);
size_t							calculate_expanded_len(const char *value,
									t_shell *state);
char							*get_var_name(const char *input, int *i_ptr);
int								is_valid_varname(char *name);
size_t							append_str_to_result(char *dest, const char *src,
									size_t j);
/* Parser */
t_command						*parser(t_token *token_lst, t_shell *state);
int								parser_loop(t_command **current_cmd,
									t_token **token_lst, t_shell *state);
t_command						*create_command(void);
void							add_redir_to_cmd(t_command *cmd,
									t_redir *new_redir);
int								count_commands(t_command *cmds);
int								has_pipe(t_command *cmds);
int								is_redirection(int type);
int								fill_argv(t_command *cmd, t_token **tok_ptr);
t_redir							*create_redir(t_token *token, int type);
int								process_redir(t_command *cmd,
									t_token **tok_ptr);
void							free_commands(t_command *cmd_head);
void							free_argv(char **argv);

/* EXECUTION & PIPELINES----------------------------------------------------- */
int								execute(t_command *cmds, t_shell *state);
void							run_child_process(t_command *cmd,
									t_shell *state);
int								execute_pipeline(t_command *cmds,
									t_shell *state);
void							run_pipeline_child(t_exec_context *ctx);
int								handle_child_status(int status);
void							setup_pipe_context(t_exec_context *ctx,
									t_command *cmd, t_shell *state,
									int prev_fd);
void							close_pipe_fds(int *prev_fd, int pipe_fd[2],
									int is_last);
int								create_pipe_if_needed(int pipe_fd[2],
									int is_last);
void							setup_input_output(int prev_fd, int pipe_fd[2],
									int is_last);
int								fork_and_handle_child(t_exec_context *ctx);
void							wait_for_child(pid_t pid, t_shell *state);

/* REDIRECTIONS & HEREDOCS--------------------------------------------------- */
int								apply_redirections(t_redir *redir_list);
int								handle_all_heredocs(t_redir *redir_list,
									t_shell *state);
int								read_single_heredoc(t_redir *redir,
									t_shell *state);
void							cleanup_heredocs(t_redir *redir_list);
int								write_heredoc_line(int fd, char *line,
									t_redir *redir, t_shell *state);
void							heredoc_sigint(int sig);
int								apply_heredoc_redir(t_redir *redir_list);
int								handle_heredocs_and_redir(t_command *cmd,
									t_shell *state);
int								cleanup_tmp(int fd, char *name);
/* Utils */
int								is_directory(const char *path);
int								save_original_fds(int *stdin_save,
									int *stdout_save);
int								restore_original_fds(int stdin_save,
									int stdout_save);
void							get_absolute_path(char **argv, t_shell *state);

/* BUILT-INS ---------------------------------------------------------------- */
int								is_builtin(char *cmd);
int								execute_builtin(char **argv, t_shell *state);
int								execute_builtin_with_redir(t_command *cmd,
									t_shell *state);
int								builtin_cd(char **argv, t_shell *state);
int								builtin_echo(char **argv);
int								builtin_env(t_shell *state);
int								builtin_exit(char **argv, t_shell *state);
int								builtin_export(char **argv, t_shell *state);
int								builtin_pwd(void);
int								builtin_unset(char **argv, t_shell *state);
void							print_env_sorted(t_shell *state);
int								ft_atoll_check(const char *str, long long *n);

/* ENVIRONMENT -------------------------------------------------------------- */
char							**create_env_copy(char **envp);
char							*get_env_value(const char *name, char **envp);
char							**find_env_var(char **envp, const char *key);
int								set_env_var(t_shell *state, const char *key,
									const char *value);
int								unset_env_var(t_shell *state, const char *key);
int								get_env_len(char **envp);

/* SIGNALS ------------------------------------------------------------------ */
void							setup_interactive_signals(void);
void							setup_non_interactive_signals(void);
void							setup_child_signals(void);
void							signal_handler(int sig);

/* UI ----------------------------------------------------------------------- */
void							display_title(void);

/* DEBUG -------------------------------------------------------------------- */
char							*get_type_name(int type);
char							*get_quote_name(int quote_type);
void							debug_print_tokens(t_token *head);

#endif
