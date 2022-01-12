/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:35:17 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/11 14:35:22 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_signal(int sig, siginfo_t *sa, void *data)
{
	(void)data;
	(void)sa;
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_replace_line ("", 1);//not sure about the diff between 0 or non zero
		rl_on_new_line ();
		rl_redisplay ();
		return ;
	}
}
