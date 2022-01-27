/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/27 16:36:00 by nel-masr         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_lxr	*lxr;
	t_env	*new_env;
	struct sigaction sa;
	t_exec	*exec;
	//int ret;
	
	(void)ac;
	(void)av;
	new_env = ft_copy_env(envp);
	if (new_env == NULL)
	{
		printf("new_env failed\n");
		return (-2);
	}
	sa.sa_sigaction = &ft_signal;
	//exec = malloc(sizeof(t_exec));
	//if (!(exec))
	//{
	//	print_parsing_error(NULL, 3);
	//	return (3);
	//}
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		line = readline("\e[1;33mminishell$ \e[0m");
		add_history(line);
		lxr = NULL;
		if (exec)
			free_exec(exec);
		exec = malloc(sizeof(t_exec));
		if (!(exec))
		{
			print_parsing_error(NULL, 3);
			return (3);
		}
		if (line)
		{
			lxr = lexer(lxr, line);
			//print_lxr(lxr);
			ft_get_expand(lxr, new_env);
			// while (lxr)
			// {
			// 	printf("exp = %s\n", lxr->value);
			// 	lxr = lxr->next;
			// }
			parser(lxr, exec);	
			//print_pipes(exec);
			execute(exec, envp);
			free(line);
		}
		//if (exec && exec->pipes)
		//{
		//	if (ft_strncmp(lxr->value, "echo ", 5) == 0)
		//		ret =ft_echo(exec->pipes);
			// if (ft_strncmp(lxr->value, "pwd ", 4) == 0)
			// 	ft_pwd();
			// else if (ft_strncmp(lxr->value, "env ", 4) == 0)
			// 	ft_env(new_env);
			// else if (ft_strncmp(lxr->value, "export ", 7) == 0)
			// {
			// 	ret = ft_export(lxr->next, new_env);
		//		if (ret == -2)
		//			return (ret);
			// }
			// else if (ft_strncmp(lxr->value, "unset ", 6) == 0)
			// {
			// 	ret = ft_unset(lxr->next, new_env);
			// 	if (ret == -2)
			// 		return (ret);
			// }
			/*while (lxr)
			{
				ret = ft_get_expand(lxr, new_env);
				printf("exp = %s\n", lxr->value);
				if (ret == -2)
					return (printf("malloc error\n"));
				lxr = lxr->next;
			}*/
		//}
		if (line == NULL)
			break ;
	}
	write(1, "\n", 1);
	write(1, "exit\n", 5);
	return (0);
}
