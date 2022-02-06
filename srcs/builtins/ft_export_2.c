/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:18:52 by aleroy            #+#    #+#             */
/*   Updated: 2022/02/06 20:18:53 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalpha_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	ft_isalnum_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	check_value_export(char *cmds, char **line)
{
	int	i;

	i = 0;
	if (cmds[i] && cmds[i] != '=' && ft_isalpha_underscore(cmds[i]) == 1)
		i++;
	if (i > 0)
		while (cmds[i] && cmds[i] != '='
			&& ft_isalnum_underscore(cmds[i]) == 1)
			i++;
	if (i == 0 || cmds[i] != '=')
		return (-1);
	*line = ft_strdup(cmds);
	if (line == NULL)
		return (-2);
	return (0);
}

int	not_in_env(t_env *envp, char *line)
{
	t_env	*tmp;

	tmp = ft_lstnew(line);
	if (tmp == NULL)
	{
		free(line);
		return (-2);
	}
	ft_lstadd_back(&envp, tmp);
	return (0);
}

int	add_line(t_env *envp, char *line)
{
	t_env	*tmp;
	int		eg;

	eg = 0;
	tmp = envp;
	while (line[eg] != '=')
		eg++;
	while (tmp)
	{
		if (ft_strncmp(tmp->line, line, eg) == 0)
		{
			free(tmp->line);
			tmp->line = ft_strdup(line);
			if (tmp->line == NULL)
				return (-2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (not_in_env(envp, line));
}
