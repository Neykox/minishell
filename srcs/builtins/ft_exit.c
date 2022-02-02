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

// int	ft_exit(int status, t_env *new_env, int nb_pipe)
// {
// 	int	ret;

// 	(void)new_env;
// 	ret = 0;
// 	if (nb_pipe == 0)
// 		ret = write(1, "exit\n", 5);
// 	if (ret < 0)
// 		return (-3);//exit(-3);
// 	printf("g_error = %d\n" , g_error);
	
// 	exit(status);

// 	// rl_replace_line (NULL, 1);//destroy char before ^C to make next line clean
// 	// rl_on_new_line ();
// 	// rl_redisplay ();
// 	return (0);
// }

int write_invalid_arg_exit(char *cmds)
{
	int	ret;

	ret = write(1, "bash: exit: ", 12);
	if (ret < 0)
		return (-3);
	ret = write(1, cmds, ft_strlen(cmds));
	if (ret < 0)
		return (-3);
	ret = write(1, ": numeric argument required\n", 28);
	if (ret < 0)
		return (-3);
	return (2);
}

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_exit(char *status, t_env *new_env, int nb_pipe)
{
	int	ret;
	int	i;

	(void)new_env;
	i = 0;
	ret = 0;
	if (nb_pipe == 0)
		ret = write(1, "exit\n", 5);
	if (ret < 0)
		return (-3);//exit(-3);
	// printf("g_error = %d\n" , g_error);
	
	while (status && status[i])
	{
		if (ft_isnum(status[i]) == 0)
			exit(write_invalid_arg_exit(status));
		i++;
	}

	if (status)
		exit(ft_atoi(status));
	exit(g_error);
	return (0);
}


// bash: exit: r: numeric argument required