/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:35:17 by aleroy            #+#    #+#             */
/*   Updated: 2022/02/03 19:23:33 by nel-masr         ###   ########.fr       */
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
		// rl_on_new_line ();//new version from discord
		rl_replace_line ("\0", 1);//destroy char before ^C to make next line clean
		rl_on_new_line ();
		rl_redisplay ();
		// usleep(2000);
		//return ;
	}
}

void	ft_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
		close(STDIN_FILENO);
	}
}

// void	ft_signal(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(0, "\n", 1);
// 		rl_replace_line ("", 0);//not sure about the diff between 0 or non zero
// 		rl_on_new_line ();
// 		rl_redisplay ();
// 		//return ;
// 	}
// }
