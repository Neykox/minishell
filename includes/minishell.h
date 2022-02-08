/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:54:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/08 14:28:04 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define VAR_ERROR		-2
# define QUOTE_ERROR	-1
# define WORD			0
# define PIPE			1
# define REDIR_STDIN	2
# define REDIR_STDOUT	3
# define SQUOTE			4
# define DQUOTE			5
# define DREDIR_LEFT	6
# define DREDIR_RIGHT	7
# define END			8
# define WSPACE			9

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

extern int				g_error;

typedef struct s_lxr	t_lxr;
typedef struct s_redir	t_redir;

struct		s_lxr
{
	int		token;
	char	*value;
	t_lxr	*next;
};

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}					t_env;

struct		s_redir
{
	char	*redir;
	int		type;
	int		fd;
	t_redir	*next;
};

typedef struct s_pipes
{
	int		nb_redir_stdout;
	int		nb_redir_stdin;
	int		nb_cmds;
	int		nb_dredir_right;
	int		nb_dredir_left;
	t_redir	*redir;
	char	**cmds;
	int		*tokens;
}				t_pipes;

typedef struct s_exec
{
	t_pipes	*pipes;
	int		nb_pipe;
	int		save;
	int		flag;
	int		status;
	int		*childpid;
	int		**pipefd;
}					t_exec;

int		main(int ac, char **av, char **envp);

/*
 * PRINT
 */

void	print_lxr(t_lxr *lxr);
void	print_pipes(t_exec *exec);
void	print_fd(t_redir *redir);

/*
 * LEXER
 */

t_lxr	*lexer(t_lxr *lexer, char *line);
t_lxr	*tokenize(t_lxr *lexer, char *line, int *i);
t_lxr	*check_notop(t_lxr *tmp, char *line, int *i);
t_lxr	*check_quote(t_lxr *tmp, char *line, int *i, char quote);

void	build_lxr(t_lxr **lxr, t_lxr *tmp);
void	build_redir_ll(t_redir **redir, t_redir *tmp);
int		verify_quote(char *line, int j, int k, char quote);
t_lxr	*append_end(t_lxr *lexer);
int		malloc_quote(char *line, int j, int k, char quote);

/*
 * SYNTAX
 */

void	print_parsing_error(char *value, int ret);
int		syntax_checker(t_lxr *lxr, t_env *new_env);
int		syntax_checker_cont(t_lxr **parser, int ret);
int		check_pipe(t_lxr **parser);
int		check_redir(t_lxr **parser);

/*
 * PARSER
 */

int		parser(t_lxr *lxr, t_exec *exec);
int		parse_values(t_lxr *lxr, t_exec *exec);
t_exec	*check_cmds(t_exec *exec);
t_lxr	*move_tmp(t_lxr *tmp, int pos);

int		check_spaces_in_cmd(char **cmds, int nb_cmds);
char	**clc(char **cmds, int *nb_cmds, int *tokens);
t_exec	*check_cmds(t_exec *exec);

int		count_commands(t_lxr *lxr, int pos, int ret);
char	**find_cmds_cont(t_lxr **tmp, char **cmds, int *i);
char	**find_commands(t_lxr *tmp, char **cmds, int *i);
char	**parse_commands(int nb_cmds, t_lxr *lxr, int pos);

int		*find_tokens_cont(t_lxr **tmp, int *tokens, int *i);
int		*find_tokens(t_lxr *tmp, int *tokens, int *i);
int		*parse_tokens(int nb_cmds, t_lxr *lxr, int pos);

t_exec	*init_exec(t_exec *exec);

/*
 * EXECUTION
 */

int		execute(t_exec *exec, char **envp, t_env *new_env, struct sigaction sa);
int		heredoc_implementation(t_redir *redir, struct sigaction sa,
			t_env *new_env);

void	close_redir_fd(t_redir *redir);
t_redir	*open_redir_fd(t_redir *redir, struct sigaction sa, t_env *new_env);
int		**init_pipefd(int **pipefd, int nb_pipe);

void	check_builtin(t_exec *exec, char *cmd, t_env *new_env);
int		builtin_checker(t_exec *exec, t_env *new_env, int ret, int i);
void	exec_commands(char **cmds, char **envp, t_env *new_env, t_exec *exec);
void	search_and_execute(t_env *tmp, char **envp, char **cmds);
int		handle_dot_slash(t_exec *exec, char **envp, char **cmds,
			t_env *new_env);

int		exec_redir(t_redir *redir);
int		open_pipe(t_exec *exec, t_env *new_env);
void	handle_pipe(t_exec *exec, t_env *new_env, int j);
void	handle_redir(t_exec *exec, t_env *new_env, int i);
void	child_work(t_exec *exec, t_env *new_env, char **envp, int i);

void	close_pipes(t_exec *exec);
void	close_fds(t_exec *exec);

/*
 * FREE
 */

void	free_everything(t_exec *exec, int *childpid, t_env *new_env);
void	free_exec(t_exec *exec);
t_lxr	*free_lxr(t_lxr *lxr);
void	free_stuff(t_exec *exec, int *childpid);
t_env	*free_env(t_env *env);
t_redir	*free_redir(t_redir *redir);
void	free_pipefd(int **pipefd, int nb_pipe);

/*
 * UTILS
 */

int		ft_isnum(int c);
int		ft_size_itoa(int n);
char	*ft_reverse(char *tab);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);;
int		ft_notop(int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(char const *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_utils(char *line, char *buf);
char	*ft_strjoin(char const *s1, char const *s2, int i);
char	**ft_split(char const *s, char c);
char	**tweaked_split(char const *s, char c);
void	t_free_that_string(char **tab);
char	*ft_add_char(char *s, char c);
char	*tweaked_strdup(const char *s);
char	*tweaked_strjoin(char const *s1, char const *s2, char const sep);

/*
 * SIGNAL
 */

void	ft_signal_heredoc(int sig);
void	ft_signal(int sig);

/*
 * BUILTINS
 */

char	*find_in_env(t_env *envp, char *line, int *ret);
int		modif_oldpwd(t_env *env);
int		modif_pwd(t_env *env);
int		ft_cd_2(t_env *env, int ret);
int		ft_cd(char **cmds, int nb_cmds, t_env *env);

char	*remove_eg(char *str);

void	ft_lstclear(t_env **lst);
void	ft_lstadd_back(t_env **alst, t_env *new);
t_env	*ft_lstnew(char *line);
t_env	*ft_copy_env(char **envp, int i, t_env *tmp);

int		check_echo_flag(char **cmds, int *n, int i, int j);
char	*ft_strjoin_utils_echo(char *line, char *buf);
char	*ft_strjoin_echo(char *s1, char *s2, int i);
int		ft_echo(char **cmds, int i, int n, char *ret);

int		ft_env(t_env *envp);

int		write_invalid_arg_exit(char *cmds);
void	ft_exit_free(t_exec *exec, t_env *new_env);
int		ft_exit_failled_write(t_exec *exec, t_env *env, char *cpy,
			char **status);
int		ft_exit_writes(t_exec *exec, t_env *env, char *cpy, char **status);
int		ft_exit(char **status, t_env *new_env, t_exec *exec, int i);

char	*ft_copy_till_exp(char *line);
int		free_exp(int *ret, char *tmp, char *exp, int i);
char	*check_exp_2(char *tmp, int *ret, t_env *env, char *value);
char	*check_exp_3(char *tmp, int *ret, char *value, int *i);
char	*check_exp(char *value, t_env *envp, int *ret, int i);

int		ft_get_expand(t_lxr *lxr, t_env *envp, int ret);
int		ft_strlen_target(char *str);
char	*remove_spaces(char *str, int i, int s, char *tmp);
char	*ft_expander(t_env *envp, char *target);

int		modif_interro(t_env *envp, char *error);
int		write_invalid_id_export(char *cmds, int *export_ret);
int		write_no_arg(t_env *env, int ret, int eg);
int		free_export(int error, int i, int ret, t_env *envp);
int		ft_export(char **cmds, t_env *envp, char *line);

int		ft_isalpha_underscore(int c);
int		ft_isalnum_underscore(int c);
int		check_value_export(char *cmds, char **line);
int		not_in_env(t_env *envp, char *line);
int		add_line(t_env *envp, char *line);

int		ft_pwd(void);

int		check_size(char *env, char *line);
void	find_line(t_env *envp, char *line);
int		write_invalid_id_unset(char *cmds, int *unset_ret);
int		free_unset(int error, char *line, int i);
int		ft_unset(char **cmds, t_env *envp, char *line);

int		check_value_unset(char *cmds, char **line);

#endif
