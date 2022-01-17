/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/14 15:23:32 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_lxr	*lxr;
	t_env	*new_env;
	struct sigaction sa;
	
	(void)ac;
	(void)av;
	new_env = ft_copy_env(envp);
	if (new_env == NULL)
		return (-2);
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
			/*if (lxr == NULL)
			{
				printf("Please close all quotes\n");
				return (1);
			}*/
			print_lxr(lxr);
			parser(lxr);	
		}
		free(line);
		if (ft_strncmp(lxr->value, "pwd ", 4) == 0)
			ft_pwd();
		if (ft_strncmp(lxr->value, "env ", 4) == 0)
			ft_env(new_env);
		// if (ft_strncmp(lxr->value, "export ", 7) == 0)
		// {
		// 	ft_export(lxr, new_env);
		// 	if (ret != 0)
		// 		return (ret);
		// }
		// if (ft_strncmp(lxr->value, "unset ", 6) == 0)
		// {
		// 	ft_unset(lxr, new_env);
		// 	if (ret != 0)
		// 		return (ret);
		// }
		if (line == NULL)
			break ;
	}
	return (0);
}
