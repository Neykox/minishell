/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:04:50 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/06 13:12:00 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_spaces_in_cmd(char **cmds, int nb_cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < nb_cmds)
	{
		while (cmds[i][j])
		{
			if (cmds[i][j] == ' ')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

char	**clc(char **cmds, int *nb_cmds)
{
	char	*tmp;
	char	**result;
	int		i;

	i = 1;
	tmp = ft_strdup(cmds[0]);
	if (tmp == NULL)
		return (NULL);
	while (i < *(nb_cmds) && cmds[i])
	{
		tmp = tweaked_strjoin(tmp, cmds[i], ' ');
		if (tmp == NULL)
			return (NULL);
		i++;
	}
	i = 0;
	t_free_that_string(cmds);
	result = ft_split(tmp, ' ');
	free(tmp);
	i = 0;
	while (result[i])
		i++;
	*(nb_cmds) = i;
	return (result);
}

t_exec	*check_cmds(t_exec *exec)
{
	int	i;
	int	ret;

	i = 0;
	if (!(exec->pipes[i].nb_cmds))
		return (exec);
	while (i <= exec->nb_pipe)
	{
		ret = check_spaces_in_cmd(exec->pipes[i].cmds, exec->pipes[i].nb_cmds);
		if (ret)
			exec->pipes[i].cmds = clc(exec->pipes[i].cmds,
					&exec->pipes[i].nb_cmds);
		i++;
	}
	return (exec);
}
