/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:19 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 15:41:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstdelone(t_env *lst)
{
	t_env *tmp;

	tmp = lst;
	free(tmp->line);
	free(tmp);
}

int check_value_unset(char *cmds, char **line)
{
	int i;

	i = 0;
	if (cmds[i] && ft_isalpha_underscore(cmds[i]) == 1)
		i++;
	if (i > 0)
		while (cmds[i] && ft_isalnum_underscore(cmds[i]) == 1)
			i++;
	if (i == 0 || (ft_isalpha_underscore(cmds[i]) == 0 && cmds[i] != '\0'))
		return (-1);
	//should be HELLO at this point
	*line = ft_strdup(cmds);
	if (*line == NULL)
		return (-2);
	return (0);
}

int check_size(char *env, char *line)
{
	int i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (ft_strlen(line) - i == 0)
		return (1);
	return (0);
}

void	find_line(t_env *envp, char *line)
{
	t_env *prev;
	t_env *curr;
	int i;

	prev = envp;
	curr = envp;
	i = 0;
	while (curr)
	{
		if (curr && check_size(curr->line, line) == 1 && ft_strncmp(curr->line, line, ft_strlen(line)) == 0)
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

int write_invalid_id_unset(char *cmds, int *unset_ret)
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

int	ft_unset(char **cmds, t_env *envp)
{
	char	*line;
	int	error;
	int	ret;
	int	i;

	line = NULL;
	ret = 0;
	i = 1;
	while (cmds[i])
	{
		error = check_value_unset(cmds[i], &line);
		if (error == -2)
		{
			g_error = 1;
			return (error);
		}
		if (ft_isalpha_underscore(cmds[i][0]) == 0)
			error = write_invalid_id_unset(cmds[i], &ret);
		if (error == -3)
		{
			g_error = 1;
			return (-3);
		}
		if (error == 0)
			find_line(envp, line);
		i++;
	}
	g_error = ret;
	return (0);
}
