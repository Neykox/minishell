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

int	ft_env(t_env *envp)
{
	int	ret;

	while (envp)
	{
		if (envp->line[0] != '?')
		{
			ret = write(1, envp->line, ft_strlen(envp->line));
			if (ret < 0)
			{
				g_error = 125;
				if (modif_interro(envp, ft_itoa(g_error)) == -2)
					return (-2);
				return (-3);
			}
			write(1, "\n", 1);
		}
		envp = envp->next;
	}
	return (g_error = 0);
}
