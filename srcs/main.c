/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/03 19:20:09 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void	init_exec(t_exec *exec)
{
	exec->cmds = NULL;
	exec->pipe_content = NULL;
	exec->redirection_stdin = NULL;
	exec->redirection_stdin = NULL;
	exec->nb_pipe = 0;
}*/

int				g_error;

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_lxr	*lxr;
	t_env	*new_env;
	struct sigaction sa;
	t_exec	*exec;
	int		ret;
	
	// (void)ac;
	(void)av;
	g_error = 0;
	ret = 0;
	// if (ac != 1)
	// {
	// 	write(1, "Please launch program without any args.\n", 40);
	// 	return (1);
	// }
	new_env = ft_copy_env(envp);
	if (new_env == NULL)
	{
		printf("new_env failed\n");
		return (-2);
	}
	ft_memset(&sa, 0, sizeof(sa));
	// sa.sa_sigaction = &ft_signal;
	sa.sa_handler = &ft_signal;
	// pid_t child = fork();
	// if (child == 0)
	// 	sa.sa_handler = SIG_IGN;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		if (ac == 1)
			line = readline("\e[1;33mminishell$ \e[0m");
		else if (ac == 2)
			line = readline("\e[1;34mminishell$ \e[0m");
		else if (ac == 3)
			line = readline("\e[1;31mminishell$ \e[0m");
		//add_history(line);
		lxr = NULL;
		if (line && line[0] !=  '\0')
		{
			add_history(line);
			lxr = lexer(lxr, line);
			printf("%d\n", g_error);
			if (lxr == NULL)
			{
				g_error = 2;
				return (2);
			}
			print_lxr(lxr);
			ft_get_expand(lxr, new_env);
			ret = syntax_checker(lxr);
			//print_pipes(exec);
			if (ret == 0)
			{
				exec = malloc(sizeof(t_exec));
				if (!(exec))
				{
					print_parsing_error(NULL, 3);
					g_error = 2;
					return (2);
				}
				/*g_error = */parse_values(lxr, exec);
				execute(exec, envp, new_env);
				free_exec(exec);
			}
			//free_lxr(lxr);
			printf("%d\n", g_error);
			//modif_interro(new_env, ft_itoa(g_error));
			free(line);
		}
		if (line == NULL)
			break ;
	}
	//write(1, "\n", 1);
	write(1, "exit\n", 5);
	return (0);//return (g_error);
}
