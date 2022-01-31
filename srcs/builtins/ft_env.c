/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:19:48 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/31 17:12:47 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		write(1, envp[i], ft_strlen(envp[i]));
// 		write(1, "\n", 1);
// 		i++;
// 	}
// }

int	ft_env(t_env *envp)
{
	int ret;

	while (envp)
	{
		ret = write(1, envp->line, ft_strlen(envp->line));
		if (ret < 0)
			break ;
		write(1, "\n", 1);
		envp = envp->next;
	}
	return (ret);
}
