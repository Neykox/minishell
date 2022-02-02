/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:43 by user42            #+#    #+#             */
/*   Updated: 2022/02/02 11:18:50 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(int status, t_env *new_env, int nb_pipe)
{
	int	ret;

	(void)new_env;
	ret = 0;
	if (nb_pipe == 0)
		ret = write(1, "exit\n", 5);
	if (ret < 0)
		return (-3);//exit(-3);
	printf("g_error = %d\n" , g_error);
	
	exit(status);

	// rl_replace_line (NULL, 1);//destroy char before ^C to make next line clean
	// rl_on_new_line ();
	// rl_redisplay ();
	return (0);
}

// void	ft_signal(s
