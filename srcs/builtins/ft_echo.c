/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:10:28 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/13 14:10:30 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_echo_flag(char *ag, int *n)
{
	if (ag[0] == '-' && ag[1] == 'n' && ag[2] == '\0')
	{
		*n = 1;
		return (2);
	}
	*n = 0;
	return (1);
}

int	ft_echo(t_pipes *pipes)
{
	int	n;
	int	i;
	char	*ret;

	i = 1;
	ret = NULL;
	printf("nb_cmds = %d\n", pipes->nb_cmds);
	if (i < pipes->nb_cmds)
		i = check_echo_flag(pipes->cmds[1], &n);
	while (i < pipes->nb_cmds && pipes->cmds[i])
	{
		ret = ft_strjoin_utils(ret, pipes->cmds[i]);
		if (ret == NULL)
			return (-2);
		i++;
		if (pipes->cmds[i])
		{
			ret = ft_strjoin_utils(ret, " ");//might segfault because freeing a non freeable var
			if (ret == NULL)
				return (-2);
		}
	}

	if (n == 0)
	{
		ret = ft_strjoin_utils(ret, "\n");//might segfault because freeing a non freeable var
		if (ret == NULL)
			return (-2);
	}
	write(1, ret, ft_strlen(ret));
	free(ret);
	return (0);
}
