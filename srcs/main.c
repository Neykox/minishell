/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/02 11:21:31 by nel-masr         ###   ########.fr       */
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
	//int ret;
	
	// (void)ac;
	(void)av;
	g_error = 0;
	if (ac != 1)
	{
		write(1, "Please launch program without any args.\n", 40);
		return (1);
	}
	new_env = ft_copy_env(envp);
	if (new_env == NULL)
	{
		printf("new_env failed\n");
		return (-2);
	}
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &ft_signal;
	//ret = 0;
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
			//print_lxr(lxr);
			ft_get_expand(lxr, new_env);
			g_error = syntax_checker(lxr);
			//print_pipes(exec);
			if (g_error == 0)
			{
				exec = malloc(sizeof(t_exec));
				if (!(exec))
				{
					print_parsing_error(NULL, 3);
					g_error = 2;
					return (2);
				}
				g_error = parse_values(lxr, exec);
				execute(exec, envp, new_env);
				free_exec(exec);
			}
			//free_lxr(lxr);
			printf("%d\n", g_error);
			free(line);
		}
		// if (exec && exec->pipes)
		// {
		/*	int ret = 0;
			if (ft_strncmp(lxr->value, "cd", 3) == 0)
				ret = ft_cd(exec->pipes->cmds, exec->nb_pipe, new_env);
			else if (ft_strncmp(lxr->value, "echo", 5) == 0)
				ret = ft_echo(exec->pipes->cmds);
			else if (ft_strncmp(lxr->value, "pwd", 4) == 0)
				ft_pwd();
			else if (ft_strncmp(lxr->value, "env", 4) == 0)
				ft_env(new_env);
			else if (ft_strncmp(lxr->value, "export", 7) == 0)
			{
				ret = ft_export(exec->pipes->cmds, new_env);
				if (ret == -2)
					return (ret);
			}
			else if (ft_strncmp(lxr->value, "unset", 6) == 0)
				ret = ft_unset(exec->pipes->cmds, new_env);
			printf("main ret = %d\n", ret);
			// 	if (ret == -2)
			// 		return (ret);
			// }
		// }*/
		if (line == NULL)
			break ;
	}
	//write(1, "\n", 1);
	write(1, "exit\n", 5);
	return (0);//return (g_error);
}
