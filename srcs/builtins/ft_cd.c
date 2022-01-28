/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:40:45 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 15:40:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// chdir(path_name);
// On success, zero is returned.  On error, -1 is returned, and
//        errno is set to indicate the error.

int	ft_cd(t_pipes *pipes, t_env *env)
{
	(void)env;
	int	ret;

	ret = 0;
	if (pipes->nb_cmds > 2)
		return (-1);
	ret = chdir(pipes->cmds[1]);
	if (ret == -1)
	{
		perror("ft_cd");
		return (-1);
	}
	//change env
	return (ret);
}
