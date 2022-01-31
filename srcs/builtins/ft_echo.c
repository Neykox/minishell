/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:10:28 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/31 17:04:30 by nel-masr         ###   ########.fr       */
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

// int	ft_echo(t_pipes *pipes)
// {
// 	int	n;
// 	int	i;
// 	char	*ret;

// 	ret = NULL;
// 	if (pipes->cmds[1])
// 		i = check_echo_flag(pipes->cmds[1], &n);
// 	while (pipes->cmds[1] && pipes->cmds[i])
// 	{
// 		ret = ft_strjoin_utils(ret, pipes->cmds[i]);
// 		if (ret == NULL)
// 			return (-2);
// 		i++;
// 		if (pipes->cmds[i])
// 		{
// 			ret = ft_strjoin_utils(ret, " ");
// 			if (ret == NULL)
// 				return (-2);
// 		}
// 	}
// 	if (n == 0 || !(pipes->cmds[1]))
// 		ret = ft_strjoin_utils(ret, "\n");
// 	else
// 		ret = ft_strjoin_utils(ret, "");
// 	if (ret == NULL)
// 		return (-2);
// 	write(1, ret, ft_strlen(ret));
// 	free(ret);
// 	return (0);
// }

int	ft_echo(char **cmds)
{
	int	n;
	int	i;
	char	*ret;
	int	ret2;

	ret = NULL;
	if (cmds[1])
		i = check_echo_flag(cmds[1], &n);
	while (cmds[1] && cmds[i])
	{
		ret = ft_strjoin_utils(ret, cmds[i]);
		if (ret == NULL)
			ret2 = -2;
		i++;
		if (cmds[i])
		{
			ret = ft_strjoin_utils(ret, " ");
			if (ret == NULL)
				ret2 = -2;
		}
	}
	if (n == 0 || !(cmds[1]))
		ret = ft_strjoin_utils(ret, "\n");
	else
		ret = ft_strjoin_utils(ret, "");
	if (ret == NULL)
		ret2 = -2;
	ret2 = write(1, ret, ft_strlen(ret));
	free(ret);
	return (ret2);
}
