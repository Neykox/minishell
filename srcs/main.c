/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/11 16:17:38 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_lxr	*lxr;

	(void)ac;
	(void)av;
	(void)envp;
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
	}
	return (0);
}
