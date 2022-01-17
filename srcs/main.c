/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/17 18:01:59 by nel-masr         ###   ########.fr       */
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
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		add_history(line);
		lxr = NULL;
		if (line)
		{
			lxr = lexer(lxr, line);
			print_lxr(lxr);
			parser(lxr);	
		}
		free(line);
		if (line == NULL)
			break ;
	}
	return (0);
}
