/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:54:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/18 17:13:44 by nel-masr         ###   ########.fr       */
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
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

typedef	struct	s_lxr	t_lxr;

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

typedef	struct	s_exec
{
	char	***cmds;
	char	**pipe_content;
	char	*redirection_stdin;
	char	*redirection_stdout;
	int		nb_pipe;
}					t_exec;

int	main(int ac, char **av, char **envp);

/*
 * PRINT
 */

void	print_lxr(t_lxr *lxr);
void	print_pipes(t_exec *exec);

/*
 * LEXER / PARSER
 */

t_lxr	*lexer(t_lxr *lexer, char *line);
t_lxr	*tokenize(t_lxr *lexer, char *line, int *i);
t_lxr	*check_notop(t_lxr *tmp, char *line, int *i);
t_lxr	*check_quote(t_lxr *tmp, char *line, int *i, char quote);
t_lxr	*append_end(t_lxr *lexer);

void	print_parsing_error(char *value, int ret);
int		syntax_checker(t_lxr *lxr);
int		parser(t_lxr *lxr, t_exec *exec);

void	build_lxr(t_lxr **lxr, t_lxr *tmp);
int		verify_quote(char *line, int j, int k, char quote);

/*
 * UTILS
 */

int	ft_notop(int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(char const *s);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_strjoin_utils(char *line, char *buf);
char    *ft_strjoin(char const *s1, char const *s2, int i);
char	*tw_strjoin(char *s1, char *s2);
void	*ft_memmove(void *dest, const void *src, size_t n);
/*
 * SIGNAL
 */

void	ft_signal(int sig, siginfo_t *sa, void *data);

/*
 * BUILTINS
 */

void    ft_pwd(void);
void    ft_env(t_env *envp);

char    *ft_copy_till_exp(char *line);
char    *check_exp(t_lxr *lxr, t_env *envp);
char    *ft_get_expand(t_lxr *lxr, t_env *envp);
char    *ft_expander(t_env *envp, char *target);

int ft_isalpha_underscore(int c);
int ft_isalnum(int c);
char    *copy_till_eg(char *line);
int check_value_export(t_lxr *lxr, char **line);
int not_in_env(t_env *envp, char *line);
int add_line(t_env *envp, char *line);
int ft_export(t_lxr *lxr, t_env *envp);

void    ft_lstdelone(t_env *lst);
int check_value_unset(t_lxr *lxr, char **line);
void    find_line(t_env *envp, char *line);
int ft_unset(t_lxr *lxr, t_env *envp);

void    ft_lstclear(t_env **lst);
void    ft_lstadd_back(t_env **alst, t_env *new);
t_env   *ft_lstnew(char *line);
t_env *ft_copy_env(char **envp);

#endif
