/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:54:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/02 16:51:00 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef	struct	s_lxr	t_lxr;
typedef	struct	s_redir	t_redir;

struct	s_lxr
{
	int		token;
	char	*value;
	t_lxr	*next;
};

typedef struct      s_env
{
    char    *line;
    struct s_env   *next;
}                   t_env;

struct	s_redir
{
	char	*redir;
	int		type;
	int		fd;
	t_redir	*next;
};

typedef	struct	s_pipes
{
	int		nb_redir_stdout;
	int		nb_redir_stdin;
	int		nb_cmds;
	int		nb_dredir_right;
	int		nb_dredir_left;
	t_redir	*redir;
	char	**cmds;
}				t_pipes;

typedef	struct	s_exec
{
	t_pipes	*pipes;
	int		nb_pipe;
}					t_exec;

int	main(int ac, char **av, char **envp);

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

/*
 * SYNTAX
 */

void	print_parsing_error(char *value, int ret);
int		syntax_checker(t_lxr *lxr);
int		syntax_checker_cont(t_lxr **parser, int ret);
int		check_pipe(t_lxr **parser);
int		check_redir(t_lxr **parser);

/*
 * PARSER
 */

int		parser(t_lxr *lxr, t_exec *exec);
int		parse_values(t_lxr *lxr, t_exec *exec);

/*
 * EXECUTION
 */

int		execute(t_exec *exec, char **envp, t_env *new_env);
int		heredoc_implementation(t_redir *redir);
void	close_redir_fd(t_redir *redir);

/*
 * FREE
 */

void	free_exec(t_exec *exec);
t_lxr	*free_lxr(t_lxr *lxr);

/*
 * UTILS
 */

int	ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);;
int		ft_notop(int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(char const *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_strjoin_utils(char *line, char *buf);
char    *ft_strjoin(char const *s1, char const *s2, int i);
char	**ft_split(char const *s, char c);
char	**tweaked_split(char const *s, char c);
char	*ft_add_char(char *s, char c);
char	*tweaked_strdup(const char *s);
char	*tweaked_strjoin(char const *s1, char const *s2, char const sep);

/*
 * SIGNAL
 */

void	ft_signal(int sig);
// void	ft_signal(int sig, siginfo_t *sa, void *data);
// void	ft_signal(int sig);

/*
 * BUILTINS
 */

// int	ft_exit(int status, t_env *new_env, int nb_pipe);
int	ft_exit(char *status, t_env *new_env, int nb_pipe);

char	*find_in_env(t_env *envp, char *line, int *ret);
int modif_oldpwd(t_env *env);
int	ft_cd(char **cmds, int nb_cmds, t_env *env);

int check_echo_flag(char *ag, int *n);
int	ft_echo(char **cmds);

int	ft_pwd(void);
int	ft_env(t_env *envp);

char    *ft_copy_till_exp(char *line);
char	*check_exp(t_lxr *lxr, t_env *envp, int *ret);
int	ft_get_expand(t_lxr *lxr, t_env *envp);
char    *ft_expander(t_env *envp, char *target);

int	ft_isalpha_underscore(int c);
int	ft_isalnum_underscore(int c);
char    *copy_till_eg(char *line);
// int check_value_export(t_lxr *lxr, char **line);
int check_value_export(char *cmds, char **line);
int not_in_env(t_env *envp, char *line);
int add_line(t_env *envp, char *line);
// int ft_export(t_lxr *lxr, t_env *envp);
int	ft_export(char **cmds, t_env *envp);

void    ft_lstdelone(t_env *lst);
// int check_value_unset(t_lxr *lxr, char **line);
int check_value_unset(char *cmds, char **line);
void    find_line(t_env *envp, char *line);
// int ft_unset(t_lxr *lxr, t_env *envp);
int ft_unset(char **cmds, t_env *envp);

void    ft_lstclear(t_env **lst);
void    ft_lstadd_back(t_env **alst, t_env *new);
t_env   *ft_lstnew(char *line);
t_env *ft_copy_env(char **envp);

#endif
