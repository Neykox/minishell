/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:54:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/17 17:30:52 by nel-masr         ###   ########.fr       */
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


int	main(int ac, char **av, char **envp);

/*
 * PRINT
 */

void	print_lxr(t_lxr *lxr);

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
int		parser(t_lxr *lxr);

void	build_lxr(t_lxr **lxr, t_lxr *tmp);
int		verify_quote(char *line, int j, int k, char quote);

/*
 * UTILS
 */

int	ft_notop(int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(char const *s);

/*
 * SIGNAL
 */

void	ft_signal(int sig, siginfo_t *sa, void *data);

#endif
