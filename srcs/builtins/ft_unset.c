/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:19 by user42            #+#    #+#             */
/*   Updated: 2022/02/04 21:06:47 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_size(char *env, char *line)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (ft_strlen(line) - i == 0)
		return (1);
	return (0);
}

void	find_line(t_env *envp, char *line)
{
	t_env	*prev;
	t_env	*curr;
	int		i;

	prev = envp;
	curr = envp;
	i = 0;
	while (curr)
	{
		if (curr && check_size(curr->line, line) == 1
			&& ft_strncmp(curr->line, line, ft_strlen(line)) == 0)
		{
			prev->next = curr->next;
			free(curr->line);
			free(curr);
			break ;
		}
		curr = curr->next;
		if (i == 1)
			prev = prev->next;
		if (i == 0)
			i++;
	}
}

int	write_invalid_id_unset(char *cmds, int *unset_ret)
{
	int	ret;

	*unset_ret = 1;
	ret = write(1, "bash: unset: `", 14);
	if (ret < 0)
		return (-3);
	ret = write(1, cmds, ft_strlen(cmds));
	if (ret < 0)
		return (-3);
	ret = write(1, "': not a valid identifier\n", 26);
	if (ret < 0)
		return (-3);
	return (-1);
}

int	free_unset(int error, char *line, int i)
{
	if (error == -2)
	{
		g_error = 1;
		return (error);
	}
	if (error == -3)
	{
		g_error = 1;
		return (-3);
	}
	if (line && i == 1)
	{
		free(line);
		line = NULL;
	}
	return (0);
}

int	ft_unset(char **cmds, t_env *envp, char *line)
{
	int	error;
	int	ret;
	int	i;

	ret = 0;
	i = 1;
	while (cmds[1] && cmds[i])
	{
		error = check_value_unset(cmds[i], &line);
		if (error == -2)
			return (free_unset(error, line, 0));
		if (ft_isalpha_underscore(cmds[i][0]) == 0)
			error = write_invalid_id_unset(cmds[i], &ret);
		if (error == -3)
			return (free_unset(error, line, 0));
		if (error == 0)
			find_line(envp, line);
		i++;
		if (line)
			free_unset(error, line, 1);
	}
	g_error = ret;
	return (0);
}
