/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/07 12:16:10 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				g_error;

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_lxr	*lxr;
	t_env	*new_env;
	struct sigaction sa;
	t_exec	*exec;
	int		ret;
	
	(void)ac;
	(void)av;
	g_error = 0;
	ret = 0;
	// if (ac != 1)
	// {
	// 	write(1, "Please launch program without any args.\n", 40);
	// 	return (1);
	// }
	new_env = ft_copy_env(envp, 0, NULL);
	if (new_env == NULL)
	{
		printf("new_env failed\n");
		return (-2);
	}
	ft_memset(&sa, 0, sizeof(sa));
	while (1)
	{
		sa.sa_handler = &ft_signal;
		sigaction(SIGINT, &sa, NULL);

		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);

		line = readline("\e[1;33mminishell$ \e[0m");
		if (g_error == 130 || g_error == 131)
			if (modif_interro(new_env, ft_itoa(g_error)) == -2)
				return (-2);

		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		lxr = NULL;
		if (line && line[0] !=  '\0')
		{
			add_history(line);
			lxr = lexer(lxr, line);
			if (lxr == NULL)
			{
				g_error = 2;
				return (2);
			}
			ft_get_expand(lxr, new_env, 0);
			ret = syntax_checker(lxr, new_env);
			if (ret == 0)
			{
				exec = malloc(sizeof(t_exec));
				if (!(exec))
				{
					print_parsing_error(NULL, 3);
					g_error = 2;
					return (2);
				}
				parse_values(lxr, exec);
				free_lxr(lxr);
				execute(exec, envp, new_env, sa);
				free_exec(exec);
			}
			free(line);
		}
		if (line == NULL)
			break ;
	}
	free_env(new_env);
	write(1, "exit\n", 5);
	return (0);
}

