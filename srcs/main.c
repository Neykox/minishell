/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/11 17:50:51 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_lxr	*lxr;
	struct sigaction sa;
	
	(void)ac;
	(void)av;
	(void)envp;
	sa.sa_sigaction = &ft_signal;
	line = readline("minishell$ ");
	add_history(line);
	while (line != NULL)
	{
		lxr = NULL;
		lxr = lexer(lxr, line);
		print_lxr(lxr);
		line = readline("minishell$ ");
		add_history(line);
		free(line);
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
