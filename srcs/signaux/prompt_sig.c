/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:35:17 by aleroy            #+#    #+#             */
/*   Updated: 2022/02/04 17:24:46 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_signal(int sig, siginfo_t *sa, void *data)
// {
// 	(void)data;
// 	(void)sa;
// 	if (sig == SIGINT)
// 	{
// 		g_error = 130;
// 		write(0, "\n", 1);
// 		// rl_on_new_line ();//new version from discord
// 		rl_replace_line ("\0", 1);//destroy char before ^C to make next line clean
// 		rl_on_new_line ();
// 		rl_redisplay ();
// 		// usleep(2000);
// 		//return ;
// 	}
// }

void	ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
		write(0, "\n", 1);
		rl_replace_line ("\0", 1);//destroy char before ^C to make next line clean
		rl_on_new_line ();
		rl_redisplay ();
	}
}

// void	ft_signal2(int sig, siginfo_t *sa, void *data)
// {
// 	(void)data;
// 	if (sig == SIGINT)
// 	{
// 		g_error = 130;
// 		write(0, "\n", 1);
// 		kill(sa->si_pid, EOF);
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		g_error = 131;
// 		write(1, "\nQuit (core dump) baby\n", 23);
// 		kill(sa->si_pid, EOF);
// 	}
// }

// void	ft_signal_heredoc(int sig, siginfo_t *sa, void *data)
// {
// 	(void)data;
// 	if (sig == SIGINT)
// 	{
// 		g_error = 130;
// 		write(1, "\n", 1);
// 		// close(STDIN_FILENO);
// 		kill(sa->si_pid, EOF);
// 	}
// }


void	ft_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}
