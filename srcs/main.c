/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/05 20:11:12 by nel-masr         ###   ########.fr       */
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

// int	main(int ac, char **av, char **envp)
// {
// 	char	*line;
// 	t_lxr	*lxr;
// 	t_env	*new_env;
// 	struct sigaction sa;
// 	struct sigaction sb;
// 	t_exec	*exec;
// 	int		ret;
	
// 	// (void)ac;
// 	(void)av;
// 	g_error = 0;
// 	ret = 0;
// 	// if (ac != 1)
// 	// {
// 	// 	write(1, "Please launch program without any args.\n", 40);
// 	// 	return (1);
// 	// }
// 	new_env = ft_copy_env(envp);
// 	if (new_env == NULL)
// 	{
// 		printf("new_env failed\n");
// 		return (-2);
// 	}
// 	ft_memset(&sa, 0, sizeof(sa));
// 	ft_memset(&sa, 0, sizeof(sb));
// 	sa.sa_flags = SA_SIGINFO;
// 	sb.sa_flags = SA_SIGINFO;
// 	while (1)
// 	{
// 		sa.sa_sigaction = &ft_signal;
// 		sigaction(SIGINT, &sa, NULL);

// 		sb.sa_sigaction = SIG_IGN;
// 		sigaction(SIGQUIT, &sb, NULL);
// 		// sb.sa_handler = SIG_IGN;
// 		// signal(SIGQUIT, SIG_IGN);

// 		//je gère le controle c (mod interactif)
// 		// sa.sa_handler = &handler
// 		//sigaction()
// 		if (ac == 1)
// 			line = readline("\e[1;33mminishell$ \e[0m");
// 		else if (ac == 2)
// 			line = readline("\e[1;34mminishell$ \e[0m");
// 		else if (ac == 3)
// 			line = readline("\e[1;31mminishell$ \e[0m");
// 		// je ne gère plus aucun signal
// 		if (g_error == 130 || g_error == 131)
// 			if (modif_interro(new_env, ft_itoa(g_error)) == -2)
// 				return (-2);
// 		// sa.sa_handler = SIG_IGN;

// 		sa.sa_sigaction = &(SIG_IGN, NULL, NULL);
// 		sigaction(SIGINT, &sa, NULL);

// 		sb.sa_sigaction = &ft_signal2;
// 		sigaction(SIGINT, &sb, NULL);
// 		sigaction(SIGQUIT, &sb, NULL);
// 		lxr = NULL;
// 		if (line && line[0] !=  '\0')
// 		{
// 			add_history(line);
// 			lxr = lexer(lxr, line);
// 			//printf("%d\n", g_error);
// 			if (lxr == NULL)
// 			{
// 				g_error = 2;
// 				return (2);
// 			}
// 			//print_lxr(lxr);
// 			ft_get_expand(lxr, new_env);
// 			ret = syntax_checker(lxr, new_env);
// 			//print_pipes(exec);
// 			if (ret == 0)
// 			{
// 				exec = malloc(sizeof(t_exec));
// 				if (!(exec))
// 				{
// 					print_parsing_error(NULL, 3);
// 					g_error = 2;
// 					return (2);
// 				}
// 				parse_values(lxr, exec);
// 				free_lxr(lxr);
// 				execute(exec, envp, new_env, sa);
// 				free_exec(exec);
// 			}
// 			//free_lxr(lxr);
// 			//print_lxr(lxr);
// 			//printf("%d\n", g_error);
// 			//modif_interro(new_env, ft_itoa(g_error));
// 			free(line);
// 		}
// 		if (line == NULL)
// 			break ;
// 	}
// 	//write(1, "\n", 1);
// 	free_env(new_env);
// 	write(1, "exit\n", 5);
// 	return (0);//return (g_error);
// }

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
	while (1)
	{
		sa.sa_handler = &ft_signal;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);

		//je gère le controle c (mod interactif)
		// sa.sa_handler = &handler
		//sigaction()
		if (ac == 1)
			line = readline("\e[1;33mminishell$ \e[0m");
		else if (ac == 2)
			line = readline("\e[1;34mminishell$ \e[0m");
		else if (ac == 3)
			line = readline("\e[1;31mminishell$ \e[0m");
		// je ne gère plus aucun signal
		if (g_error == 130)
			if (modif_interro(new_env, ft_itoa(g_error)) == -2)
				return (-2);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		lxr = NULL;
		if (line && line[0] !=  '\0')
		{
			add_history(line);
			lxr = lexer(lxr, line);
			//printf("%d\n", g_error);
			if (lxr == NULL)
			{
				g_error = 2;
				return (2);
			}
			//print_lxr(lxr);
			ft_get_expand(lxr, new_env);
			ret = syntax_checker(lxr, new_env);
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
				parse_values(lxr, exec);
				free_lxr(lxr);
				execute(exec, envp, new_env, sa);
				free_exec(exec);
			}
			else
				free_lxr(lxr);
			//free_lxr(lxr);
			//print_lxr(lxr);
			//printf("%d\n", g_error);
			//modif_interro(new_env, ft_itoa(g_error));
			free(line);
		}
		else if (line == NULL)
			break ;
	}
	//write(1, "\n", 1);
	free_env(new_env);
	write(1, "exit\n", 5);
	return (0);//return (g_error);
}

