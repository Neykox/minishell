/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:53:56 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/07 15:53:07 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				g_error;

void	signal_shit(struct sigaction sa, int i)
{
	if (i == 1)
	{
		sa.sa_handler = &ft_signal;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	if (i == 2)
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}

int	send_to_exec(t_lxr *lxr, char **envp, t_env *new_env, struct sigaction sa)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!(exec))
	{
		print_parsing_error(NULL, 3);
		g_error = 2;
		return (-2);
	}
	parse_values(lxr, exec);
	free_lxr(lxr);
	execute(exec, envp, new_env, sa);
	free_exec(exec);
	return (0);
}

int	line_found(struct sigaction sa, char *cpy, t_env *new_env, char **envp)
{
	int		ret;
	t_lxr	*lxr;
	int		ret_exec;

	lxr = NULL;
	add_history(cpy);
	lxr = lexer(lxr, cpy);
	if (lxr == NULL)
	{
		g_error = 2;
		return (-2);
	}
	ft_get_expand(lxr, new_env, 0);
	ret = syntax_checker(lxr, new_env);
	if (ret == 0)
	{
		ret_exec = send_to_exec(lxr, envp, new_env, sa);
		if (ret_exec == -2)
			return (-2);
	}
	else
		free_lxr(lxr);
	return (0);
}

int	rl_loop(struct sigaction sa, t_env *new_env, char **envp)
{
	char	*line;
	int		ret;

	while (1)
	{
		signal_shit(sa, 1);
		line = readline("\e[1;33mminishell$ \e[0m");
		if (g_error == 130 || g_error == 131)
			if (modif_interro(new_env, ft_itoa(g_error)) == -2)
				return (-2);
		signal_shit(sa, 2);
		if (line && line[0] != '\0')
		{
			ret = line_found(sa, line, new_env, envp);
			if (ret == -2)
				return (-2);
			free(line);
		}
		else if (line == NULL)
			break ;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_env				*new_env;
	struct sigaction	sa;
	int					ret;

	(void)av;
	g_error = 0;
	ret = 0;
	if (ac != 1)
	{
		write(1, "Please launch program without any args.\n", 40);
		return (1);
	}
	new_env = ft_copy_env(envp, 0, NULL);
	if (new_env == NULL)
		return (-2);
	ft_memset(&sa, 0, sizeof(sa));
	ret = rl_loop(sa, new_env, envp);
	if (ret == -2)
		return (-2);
	free_env(new_env);
	write(1, "exit\n", 5);
	return (0);
}
