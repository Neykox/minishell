/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/10 15:20:31 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	// t_lxr	*lxr;
	struct sigaction sa;

	sa.sa_sigaction = &ft_signal;
	line = readline("minishell$ ");
	add_history(line);
	while (line != NULL)
	{
		// lxr = lexer(lxr, line);
		line = readline("minishell$ ");
		// printf("%s",line);
		add_history(line);
		free(line);
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
